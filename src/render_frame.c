/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:55 by chughes           #+#    #+#             */
/*   Updated: 2023/01/18 13:47:39 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

// Renders next frame from map to window
int	render_frame(void)
{
	t_data	*data;
	coord_t ray_dir;
	int	x;

	data = get_data();
	x = 0;
	while (x < WIDTH)
	{

		ray_dir = ray_direction(x);
		
		int map_x = (int)data->pos[X];
		int map_y = (int)data->pos[Y];

		//length of ray from current position to next x or y-side
		coord_t side_dist;

		//length of ray from one x or y-side to next x or y-side
		coord_t delta_dist;
		if (ray_dir[X] == 0)
			delta_dist[X] = 0;
		else
			delta_dist[X] = fabs(1 / ray_dir[X]);
		if (ray_dir[Y] == 0)
			delta_dist[Y] = 0;
		else
			delta_dist[Y] = fabs(1 / ray_dir[Y]);
		double perp_wall_dist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int step_x;
		int step_y;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (ray_dir[X] < 0) {
			step_x = -1;
			side_dist[X] = (data->pos[X] - map_x) * delta_dist[X];
		} else {
			step_x = 1;
			side_dist[X] = (map_x + 1.0 - data->pos[X]) * delta_dist[X];
		}
		if (ray_dir[Y] < 0) {
			step_y = -1;
			side_dist[Y] = (data->pos[Y] - map_y) * delta_dist[Y];
		} else {
			step_y = 1;
			side_dist[Y] = (map_y + 1.0 - data->pos[Y]) * delta_dist[Y];
		}

		while (hit == 0) {
			//jump to next map square, OR in x-direction, OR in y-direction
			if (side_dist[X] < side_dist[Y]) {
				side_dist[X] += delta_dist[X];
				map_x += step_x;
				side = 0;
			} else {
				side_dist[Y] += delta_dist[Y];
				map_y += step_y;
				side = 1;
			}
			//Check if ray has hit a wall
			if (data->map[map_x][map_y] > 0)
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map_x - data->pos[X] + (1 - step_x) / 2) / ray_dir[X];
		else
			perp_wall_dist = (map_y - data->pos[Y] + (1 - step_y) / 2) / ray_dir[Y];

		//Calculate HEIGHT of line to draw on screen
		int line_height = (int)(HEIGHT / perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		int draw_start = -line_height / 2 + HEIGHT / 2;
		if(draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + HEIGHT / 2;
		if(draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;

		ver_line(data, x, draw_start, draw_end, side);
		
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}