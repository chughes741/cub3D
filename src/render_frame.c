/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:55 by chughes           #+#    #+#             */
/*   Updated: 2023/01/19 16:25:16 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Sets frame->ray_dir
void	ray_direction(t_data *data, t_frame *frame)
{
	if (frame->x != 0)
	{
		frame->camera_x = 2 * frame->x / (double)WIDTH - 1;
		frame->ray_dir[X] = data->dir_x + data->plane_x * frame->camera_x;
		frame->ray_dir[Y] = data->dir_y + data->plane_y * frame->camera_x;
	}
	else
	{
		frame->camera_x = 0;
		frame->ray_dir[X] = data->dir_x;
		frame->ray_dir[Y] = data->dir_y;
	} 
}

// Length of ray from one x or y-side to next x or y-side
void	ray_length(t_frame *frame)
{
	if (frame->ray_dir[X] == 0)
		frame->delta_dst[X] = 0;
	else
		frame->delta_dst[X] = fabs(1 / frame->ray_dir[X]);
	if (frame->ray_dir[Y] == 0)
		frame->delta_dst[Y] = 0;
	else
		frame->delta_dst[Y] = fabs(1 / frame->ray_dir[Y]);
}


// Evaluates distance to wall hit
void	side_distance(t_data *data, t_frame *frame)
{
	if (frame->ray_dir[X] < 0) {
		frame->step[X] = -1;
		frame->side_dst[X] = (data->pos_x - frame->map[X]) * frame->delta_dst[X];
	} else {
		frame->step[X] = 1;
		frame->side_dst[X] = (frame->map[X] + 1.0 - data->pos_x) * frame->delta_dst[X];
	}
	if (frame->ray_dir[Y] < 0) {
		frame->step[Y] = -1;
		frame->side_dst[Y] = (data->pos_y - frame->map[Y]) * frame->delta_dst[Y];
	} else {
		frame->step[Y] = 1;
		frame->side_dst[Y] = (frame->map[Y] + 1.0 - data->pos_y) * frame->delta_dst[Y];
	}
}

// Extends ray until it finds a wall
void	check_hit(t_data *data, t_frame *frame)
{
	frame->hit = false;
	while (frame->hit == false) {
		//jump to next map square, OR in x-direction, OR in y-direction
		if (frame->side_dst[X] < frame->side_dst[Y]) {
			frame->side_dst[X] += frame->delta_dst[X];
			frame->map[X] += frame->step[X];
			frame->side = 0;
		} else {
			frame->side_dst[Y] += frame->delta_dst[Y];
			frame->map[Y] += frame->step[Y];
			frame->side = 1;
		}
		//Check if ray has hit a wall
		if (data->map[frame->map[X]][frame->map[Y]] > 0)
			frame->hit = true;
	}
}

// Sets line height of current wall in view
void	get_line_height(t_data *data, t_frame *frame)
{
	double	perp_wall_dist;
	double	temp[2];

	temp[X] = (frame->map[X] - data->pos_x + (1 - frame->step[X]) / 2);
	temp[Y] = (frame->map[Y] - data->pos_y + (1 - frame->step[Y]) / 2);
	if (frame->side == 0)
		perp_wall_dist = temp[X] / frame->ray_dir[X];
	else
		perp_wall_dist = temp[Y] / frame->ray_dir[Y];
	frame->line_height = (int)(HEIGHT / perp_wall_dist);
}

// Draws full vertical line to data->img
void	draw_line(t_data *data, t_frame *frame)
{
	int draw_start;
	int draw_end;
	int	pixel;
	int	color = 0xFFFF00;

	draw_start = -frame->line_height / 2 + HEIGHT / 2;
	draw_end = frame->line_height / 2 + HEIGHT / 2;
	if(draw_start < 0)
		draw_start = 0;
	if(draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	if (frame->side == 1)
		color = color / 2;
	pixel = -1;
	while (++pixel < draw_start)
		mlx_pixel_img(frame->x, pixel, data->floor);
	while (++pixel < draw_end)
		mlx_pixel_img(frame->x, pixel, color);
	while (++pixel < HEIGHT)
		mlx_pixel_img(frame->x, pixel, data->ceiling);
}

// Renders next frame from map to window
int	render_frame(void)
{
	t_data	*data;
	t_frame	*frame;

	data = get_data();
	frame = xalloc(1, sizeof(t_frame));
	while (frame->x < WIDTH)
	{
		ray_direction(data, frame);
		frame->map[X] = (int)data->pos_x;
		frame->map[Y] = (int)data->pos_y;
		ray_length(frame);
		side_distance(data, frame);
		check_hit(data, frame);
		get_line_height(data, frame);
		draw_line(data, frame);
		frame->x++;
	}
	frame = xfree(frame);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
