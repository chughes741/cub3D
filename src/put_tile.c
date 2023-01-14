/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_tile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:51 by chughes           #+#    #+#             */
/*   Updated: 2023/01/14 17:00:49 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Draws tile to screen
void	put_tile(char tile, int x, int y)
{
	t_data	*data;

	data = get_data();
	if (tile == '0')
		mlx_put_image_to_window(data->mlx, data->win, data->east, x, y);
	else if (tile == 'C')
		mlx_put_image_to_window(data->mlx, data->win, data->west, x, y);
	else if (tile == 'P')
		mlx_put_image_to_window(data->mlx, data->win, data->north, x, y);
	else
		mlx_put_image_to_window(data->mlx, data->win, data->south, x, y);
	return ;
}
