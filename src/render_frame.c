/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:55 by chughes           #+#    #+#             */
/*   Updated: 2023/01/23 14:23:59 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Sets frame->ray_dir
void	ray_direction(t_data *data, t_frame *frame)
{
	frame->camera_x = 2 * frame->x / (double)WIDTH - 1;
	frame->ray_dir[X] = data->dir[X] + data->plane[X] * frame->camera_x;
	frame->ray_dir[Y] = data->dir[Y] + data->plane[Y] * frame->camera_x;
}

// Length of ray from one x or y-side to next x or y-side
void	ray_length(t_frame *frame)
{
	frame->delta_dst[X] = fabs(1 / frame->ray_dir[X]);
	frame->delta_dst[Y] = fabs(1 / frame->ray_dir[Y]);
}

// Evaluates distance to wall hit
void	side_distance(t_data *data, t_frame *frame)
{
	if (frame->ray_dir[X] < 0)
	{
		frame->step[X] = -1;
		frame->side_dst[X] = (data->pos[X] - frame->map[X]) * frame->delta_dst[X];
	}
	else
	{
		frame->step[X] = 1;
		frame->side_dst[X] = (frame->map[X] + 1.0 - data->pos[X]) * frame->delta_dst[X];
	}
	if (frame->ray_dir[Y] < 0)
	{
		frame->step[Y] = -1;
		frame->side_dst[Y] = (data->pos[Y] - frame->map[Y]) * frame->delta_dst[Y];
	}
	else
	{
		frame->step[Y] = 1;
		frame->side_dst[Y] = (frame->map[Y] + 1.0 - data->pos[Y]) * frame->delta_dst[Y];
	}
}

// Extends ray until it finds a wall
void	check_hit(t_data *data, t_frame *frame)
{
	frame->hit = false;
	while (frame->hit == false)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (frame->side_dst[X] < frame->side_dst[Y])
		{
			frame->side_dst[X] += frame->delta_dst[X];
			frame->map[X] += frame->step[X];
			if (frame->step[X] > 0)
				frame->side = NORTH;
			else
				frame->side = SOUTH;
		}
		else
		{
			frame->side_dst[Y] += frame->delta_dst[Y];
			frame->map[Y] += frame->step[Y];
			if (frame->step[Y] > 0)
				frame->side = EAST;
			else
				frame->side = WEST;
		}
		//Check if ray has hit a wall
		if (data->map[frame->map[X]][frame->map[Y]] > 0)
			frame->hit = true;
	}
}

// Sets line height of current wall in view
void	get_line_height(t_data *data, t_frame *frame)
{
	double	temp[2];

	temp[X] = (frame->map[X] - data->pos[X] + (1 - frame->step[X]) / 2);
	temp[Y] = (frame->map[Y] - data->pos[Y] + (1 - frame->step[Y]) / 2);
	if (frame->side == NORTH || frame->side == SOUTH)
		frame->perp_dst = temp[X] / frame->ray_dir[X];
	if (frame->side == EAST || frame->side == WEST)
		frame->perp_dst = temp[Y] / frame->ray_dir[Y];
	frame->line_height = (int)(HEIGHT / frame->perp_dst);
}

// Finds x value of ray cast on a wall
void	wall_texture_x(t_data *data, t_frame *frame)
{
	if (frame->side == NORTH || frame->side == SOUTH)
		frame->wall_x = data->pos[Y] + frame->perp_dst * frame->ray_dir[Y];
	if (frame->side == EAST || frame->side == WEST)
		frame->wall_x = data->pos[X] + frame->perp_dst * frame->ray_dir[X];
	frame->wall_x -= floor(frame->wall_x);
}

// Gets line height of texture to draw
void	draw_length(t_frame *frame)
{
	frame->draw_start = -frame->line_height / 2 + HEIGHT / 2;
	frame->draw_end = frame->line_height / 2 + HEIGHT / 2;
	if (frame->draw_start < 0)
		frame->draw_start = 0;
	if (frame->draw_end >= HEIGHT)
		frame->draw_end = HEIGHT - 1;
}

// Draws full vertical line to data->img
void	draw_line(t_data *data, t_frame *frame)
{
	int		pixel;
	int		color;
	int		tex[2];
	double	tex_step;
	double	tex_pos;

	wall_texture_x(data, frame);
	// x coordinate on the texture
	tex[X] = frame->wall_x * TEX_WIDTH;
	if ((frame->side == NORTH || frame->side == SOUTH) && frame->ray_dir[X] > 0)
		tex[X] = TEX_WIDTH - tex[X] - 1;
	if ((frame->side == EAST || frame->side == WEST) && frame->ray_dir[Y] < 0)
		tex[X] = TEX_WIDTH - tex[X] - 1;
	draw_length(frame);
	pixel = -1;
	while (++pixel < frame->draw_start)
		mlx_pixel_img(frame->x, pixel, data->floor);
	tex_step = 1.0 * TEX_HEIGHT / frame->line_height;
	tex_pos = (frame->draw_start - HEIGHT / 2 + frame->line_height / 2) * tex_step;
	while (++pixel < frame->draw_end)
	{
		tex[Y] = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += tex_step;
		color = data->tex[frame->side][TEX_HEIGHT * tex[Y] + tex[X]];
		mlx_pixel_img(frame->x, pixel, color);
	}
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
		frame->map[X] = (int)data->pos[X];
		frame->map[Y] = (int)data->pos[Y];
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
