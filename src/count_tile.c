/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:14 by chughes           #+#    #+#             */
/*   Updated: 2023/01/14 16:29:15 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	count_tile(int x, int y)
{
	t_data	*data;

	data = get_data();
	if (data->map[y][x] == 'P')
	{
		data->x_p = x;
		data->y_p = y;
		data->map[y][x] = '0';
		data->n_p += 1;
	}
	else if (data->map[y][x] == 'C')
		data->n_col += 1;
	else if (data->map[y][x] == 'E')
		data->n_ex += 1;
	else if (data->map[y][x] == '0' || data->map[y][x] == '1')
		data->n_col += 0;
	else
		exit_error();
}
