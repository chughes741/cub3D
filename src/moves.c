/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:38 by chughes           #+#    #+#             */
/*   Updated: 2023/01/14 16:29:42 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Checks if the current tile is a collectable or exit
void	check_tile(void)
{
	t_data	*d;

	d = get_data();
	if (d->map[d->y_p][d->x_p] == 'C')
	{
		d->map[d->y_p][d->x_p] = '0';
		d->n_col -= 1;
	}
	if (d->map[d->y_p][d->x_p] == 'E' && d->n_col == 0)
		close_window(&d);
	return ;
}

// Move player sprite up one space
void	move_up(t_data **data)
{
	t_data	*d;

	d = (*data);
	if (d->map[d->y_p - 1][d->x_p] == '1')
		return ;
	d->y_p -= 1;
	d->moves += 1;
	printf("%i\n", d->moves);
	return ;
}

// Move player sprite down one space
void	move_dn(t_data **data)
{
	t_data	*d;

	d = (*data);
	if (d->map[d->y_p + 1][d->x_p] == '1')
		return ;
	d->y_p += 1;
	d->moves += 1;
	printf("%i\n", d->moves);
	return ;
}

// Move player sprite left one space
void	move_lf(t_data **data)
{
	t_data	*d;

	d = (*data);
	if (d->map[d->y_p][d->x_p - 1] == '1')
		return ;
	d->x_p -= 1;
	d->moves += 1;
	printf("%i\n", d->moves);
	return ;
}

// Move player sprite right one space
void	move_rg(t_data **data)
{
	t_data	*d;

	d = (*data);
	if (d->map[d->y_p][d->x_p + 1] == '1')
		return ;
	d->x_p += 1;
	d->moves += 1;
	printf("%i\n", d->moves);
	return ;
}
