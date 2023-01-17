/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:38 by chughes           #+#    #+#             */
/*   Updated: 2023/01/17 14:55:04 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Move player sprite north
void	move_north(t_data **data)
{
	t_data	*d;

	d = (*data);
	return ;
}

// Move player sprite east
void	move_east(t_data **data)
{
	t_data	*d;

	d = (*data);
	return ;
}

// Move player sprite south
void	move_south(t_data **data)
{
	t_data	*d;

	d = (*data);
	return ;
}

// Move player sprite west
void	move_west(t_data **data)
{
	t_data	*d;

	d = (*data);
	return ;
}

// Turns the camera left
void look_left(t_data **data)
{
	t_data *d;

	d = (*data);
	double oldDirX = d->dir_x;
	d->dir_x = d->dir_x * cos(d->rot_speed) - d->dir_y * sin(d->rot_speed);
	d->dir_y = oldDirX * sin(d->rot_speed) + d->dir_y * cos(d->rot_speed);
	double oldPlane_x = d->plane_x;
	d->plane_x = d->plane_x * cos(d->rot_speed) - d->plane_y * sin(d->rot_speed);
	d->plane_y = oldPlane_x * sin(d->rot_speed) + d->plane_y * cos(d->rot_speed);
}

// Turns the camera right
void look_right(t_data **data)
{
	t_data *d;

	d = (*data);
	double oldDirX = d->dir_x;
	d->dir_x = d->dir_x * cos(-d->rot_speed) - d->dir_y * sin(-d->rot_speed);
	d->dir_y = oldDirX * sin(-d->rot_speed) + d->dir_y * cos(-d->rot_speed);
	double oldPlane_x = d->plane_x;
	d->plane_x = d->plane_x * cos(-d->rot_speed) - d->plane_y * sin(-d->rot_speed);
	d->plane_y = oldPlane_x * sin(-d->rot_speed) + d->plane_y * cos(-d->rot_speed);
}
