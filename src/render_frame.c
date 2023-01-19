/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:55 by chughes           #+#    #+#             */
/*   Updated: 2023/01/17 18:27:54 by chughes          ###   ########.fr       */
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

// Renders next frame from map to window
int	render_frame(void)
{
	t_data	*data;
	int	x;

	data = get_data();
	x = 0;
	while (x < WIDTH)
	{
		double camera_x;
		double ray_dir_x;
		double ray_dir_y;
		if (x != 0)
		{
			camera_x = 2 * x / (double)WIDTH - 1;
			ray_dir_x = data->dir_x + data->plane_x * camera_x;
			ray_dir_y = data->dir_y + data->plane_y * camera_x;
		}
		else
		{
			camera_x = 0;
			ray_dir_x = data->dir_x;
			ray_dir_y = data->dir_y;
		} 
		
		int map_x = (int)data->pos_x;
		int map_y = (int)data->pos_y;

		//length of ray from current position to next x or y-side
		double side_dist_x;
		double side_dist_y;
		
		//length of ray from one x or y-side to next x or y-side
		double delta_dist_x;
		if (ray_dir_x == 0)
			delta_dist_x = 0;
		else
			delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y;
		if (ray_dir_y == 0)
			delta_dist_y = 0;
		else
			delta_dist_y = fabs(1 / ray_dir_y);
		double perp_wall_dist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int step_x;
		int step_y;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (ray_dir_x < 0) {
			step_x = -1;
			side_dist_x = (data->pos_x - map_x) * delta_dist_x;
		} else {
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0) {
			step_y = -1;
			side_dist_y = (data->pos_y - map_y) * delta_dist_y;
		} else {
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->pos_y) * delta_dist_y;
		}

		while (hit == 0) {
			//jump to next map square, OR in x-direction, OR in y-direction
			if (side_dist_x < side_dist_y) {
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			} else {
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			//Check if ray has hit a wall
			if (data->map[map_x][map_y] > 0)
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map_x - data->pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - data->pos_y + (1 - step_y) / 2) / ray_dir_y;

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