/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:06 by chughes           #+#    #+#             */
/*   Updated: 2023/01/14 16:29:08 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Cleans up and exits program
int	exit_window(int keycode, t_data **data)
{
	keycode = 0;
	if (*data)
		del_data();
	exit(0);
}

// Closes window, cleans up, and exits
void	close_window(t_data **data)
{
	mlx_destroy_window((*data)->mlx, (*data)->win);
	del_data();
	exit(0);
}

// Checks key presses
int	keydown(int keycode, t_data **data)
{
	if (keycode == 53)
		close_window(data);
	if (keycode == 13)
		move_up(data);
	if (keycode == 1)
		move_dn(data);
	if (keycode == 0)
		move_lf(data);
	if (keycode == 2)
		move_rg(data);
	check_tile();
	return (0);
}