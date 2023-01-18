/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:55 by chughes           #+#    #+#             */
/*   Updated: 2023/01/18 14:34:40 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Returns the fractional bits of num
double	frac(double num)
{
	double fractional_part;

	fractional_part = remainder(num, 1.0);
	return (fractional_part);
}

void	mlx_pixel_img(int x, int y, int color)
{
	t_data	*data;
	char	*dst;

	data = get_data();
	dst = data->addr + (y * data->line_size + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	ver_line(t_data *data, int x, int y1, int y2, int side)
{
	int	pixel;

	int	color;
	color = 0xFFFF00;
	if (side == 1)
		color = color / 2;

	pixel = -1;
	while (++pixel < y1)
		mlx_pixel_img(x, pixel, data->floor);
	while (++pixel < y2)
		mlx_pixel_img(x, pixel, color);
	while (++pixel < HEIGHT)
		mlx_pixel_img(x, pixel, data->ceiling);
}

// Returns a coord_t with the ray direction vector
coord_t	ray_direction(int x)
{
	t_data	*data;
	coord_t	ray_dir;
	double	camera_x;

	data = get_data();
	camera_x = 2 * x / WIDTH.0 - 1.0;
	ray_dir[X] = data->dir[X] + data->plane[X] * camera_x;
	ray_dir[Y] = data->dir[Y] + data->plane[Y] * camera_x;
	return (ray_dir); 
}

// Length of ray from one x or y-side to next x or y-side
coord_t	delta_distance(coord_t ray_dir)
{
	coord_t	delta_dst;

	if (ray_dir[X] == 0)
		delta_dst[X] = 0;
	else
		delta_dst[X] = fabs(1 / ray_dir[X]);
	if (ray_dir[Y] == 0)
		delta_dst[Y] = 0;
	else
		delta_dst[Y] = fabs(1 / ray_dir[Y]);
	return (delta_dst);
}

// Direction to step in x or y-direction (either +1 or -1)
coord_t	step_direction(coord_t *side_dst, coord_t delta_dst)
{
	t_data	*data;
	coord_t	step;
	
	data = get_data();
	if (ray_dir[X] < 0) {
		step[X] = -1;
		side_dst[X] = frac(data->pos[X]) * delta_dst[X];
	} else {
		step[X] = 1;
		side_dst[X] = (1.0 + frac(data->pos[X])) * delta_dst[X];
	}
	if (ray_dir[Y] < 0) {
		step[Y] = -1;
		side_dst[Y] = frac(data->pos[Y]) * delta_dst[Y];
	} else {
		step[Y] = 1;
		side_dst[Y] = (1.0 + frac)data->pos[Y])) * delta_dst[Y];
	}
	return (step);
}

int	find_wall(coord_t side_dst, coord_t step, coord_t delta_dst)
{
	t_data	data;
	coord_t	map;
	int hit;
	int side;

	data = get_data();
	map[X] = data->map[X];
	map[Y] = data->map[Y];
	hit = 0;
	while (hit == 0)
	{
		if (side_dst[X] < side_dst[Y])
		{
			side_dst[X] += delta_dst[X];
			map[X] += step[X];
			side = 0;
		}
		else
		{
			side_dst[Y] += delta_dst[Y];
			map[Y] += step[Y];
			side = 1;
		}
		if (data->map[map[X]][map[Y]] > 0)
			hit = 1;
	}
	return (side);	
}

// Draws a vertical line onto img
void	draw_line(t_data *d, coord_t ray_dir, coord_t delta_dst)
{
	coord_t side_dst;
	coord_t	step;
	double	perp_wall_dist;
	int		draw_start;
	int		draw_end;

	step = step_direction(&side_dst, delta_dst);
	if (find_wall(side_dst, step, delta_dst, map) == 0)
		perp_wall_dist = (frac(d->pos[X]) + (1 - step[X]) / 2) / ray_dir[X];
	else
		perp_wall_dist = (frac(d->pos[Y]) + (1 - step[Y]) / 2) / ray_dir[Y];
	draw_start = -(HEIGHT / perp_wall_dist) / 2 + HEIGHT / 2;
	if(draw_start < 0)
		draw_start = 0;
	draw_end = (HEIGHT / perp_wall_dist) / 2 + HEIGHT / 2;
	if(draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;

	ver_line(d, x, draw_start, draw_end, side);
}


// Renders next frame from map to window
int	render_frame(void)
{
	t_data	*data;
	coord_t ray_dir;
	coord_t delta_dst;
	int	x;

	data = get_data();
	x = 0;
	while (x < WIDTH)
	{
		ray_dir = ray_direction(x);
		delta_dst = delta_distance(ray_dir);
		draw_line(data, ray_dir);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
