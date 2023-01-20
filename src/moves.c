/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:38 by chughes           #+#    #+#             */
/*   Updated: 2023/01/17 17:08:06 by chughes          ###   ########.fr       */
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
	d->dir_x = d->dir_x * cos(ROT_SPEED) - d->dir_y * sin(ROT_SPEED);
	d->dir_y = oldDirX * sin(ROT_SPEED) + d->dir_y * cos(ROT_SPEED);
	double oldPlane_x = d->plane_x;
	d->plane_x = d->plane_x * cos(ROT_SPEED) - d->plane_y * sin(ROT_SPEED);
	d->plane_y = oldPlane_x * sin(ROT_SPEED) + d->plane_y * cos(ROT_SPEED);
}

// Turns the camera right
void look_right(t_data **data)
{
	t_data *d;

	d = (*data);
	double oldDirX = d->dir_x;
	d->dir_x = d->dir_x * cos(-ROT_SPEED) - d->dir_y * sin(-ROT_SPEED);
	d->dir_y = oldDirX * sin(-ROT_SPEED) + d->dir_y * cos(-ROT_SPEED);
	double oldPlane_x = d->plane_x;
	d->plane_x = d->plane_x * cos(-ROT_SPEED) - d->plane_y * sin(-ROT_SPEED);
	d->plane_y = oldPlane_x * sin(-ROT_SPEED) + d->plane_y * cos(-ROT_SPEED);
}
