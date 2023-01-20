/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:38 by chughes           #+#    #+#             */
/*   Updated: 2023/01/20 15:37:45 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Move player sprite north
void	move_north(t_data **data)
{
	t_data	*d;

	d = (*data);
	if (!d->map[(int)(d->pos[X] + d->dir[X] * MOVE_SPEED)][(int)(d->pos[Y])])
		d->pos[X] += d->dir[X] * MOVE_SPEED;
	if (!d->map[(int)(d->pos[X])][(int)(d->pos[Y] + d->dir[Y] * MOVE_SPEED)])
		d->pos[Y] += d->dir[Y] * MOVE_SPEED;
	return ;
}

// Move player sprite east
void	move_east(t_data **data)
{
	t_data	*d;

	d = (*data);
	if (!d->map[(int)(d->pos[X] + d->dir[X] * MOVE_SPEED)][(int)(d->pos[Y])])
		d->pos[X] += d->dir[Y] * MOVE_SPEED;
	if (!d->map[(int)(d->pos[X])][(int)(d->pos[Y] + d->dir[Y] * MOVE_SPEED)])
		d->pos[Y] -= d->dir[X] * MOVE_SPEED;
	return ;
}

// Move player sprite south
void	move_south(t_data **data)
{
	t_data	*d;

	d = (*data);
	if (!d->map[(int)(d->pos[X] - d->dir[X] * MOVE_SPEED)][(int)(d->pos[Y])])
		d->pos[X] -= d->dir[X] * MOVE_SPEED;
	if (!d->map[(int)(d->pos[X])][(int)(d->pos[Y] - d->dir[Y] * MOVE_SPEED)])
		d->pos[Y] -= d->dir[Y] * MOVE_SPEED;
	return ;
}

// Move player sprite west
void	move_west(t_data **data)
{
	t_data	*d;

	d = (*data);
	if (!d->map[(int)(d->pos[X] - d->dir[X] * MOVE_SPEED)][(int)(d->pos[Y])])
		d->pos[X] -= d->dir[Y] * MOVE_SPEED;
	if (!d->map[(int)(d->pos[X])][(int)(d->pos[Y] - d->dir[Y] * MOVE_SPEED)])
		d->pos[Y] += d->dir[X] * MOVE_SPEED;
	return ;
}

// Turns the camera left
void look_left(t_data **data)
{
	t_data *d;

	d = (*data);
	double oldDirX = d->dir[X];
	d->dir[X] = d->dir[X] * cos(ROT_SPEED) - d->dir[Y] * sin(ROT_SPEED);
	d->dir[Y] = oldDirX * sin(ROT_SPEED) + d->dir[Y] * cos(ROT_SPEED);
	double oldPlane_x = d->plane[X];
	d->plane[X] = d->plane[X] * cos(ROT_SPEED) - d->plane[Y] * sin(ROT_SPEED);
	d->plane[Y] = oldPlane_x * sin(ROT_SPEED) + d->plane[Y] * cos(ROT_SPEED);
}

// Turns the camera right
void look_right(t_data **data)
{
	t_data *d;

	d = (*data);
	double oldDirX = d->dir[X];
	d->dir[X] = d->dir[X] * cos(-ROT_SPEED) - d->dir[Y] * sin(-ROT_SPEED);
	d->dir[Y] = oldDirX * sin(-ROT_SPEED) + d->dir[Y] * cos(-ROT_SPEED);
	double oldPlane_x = d->plane[X];
	d->plane[X] = d->plane[X] * cos(-ROT_SPEED) - d->plane[Y] * sin(-ROT_SPEED);
	d->plane[Y] = oldPlane_x * sin(-ROT_SPEED) + d->plane[Y] * cos(-ROT_SPEED);
}
