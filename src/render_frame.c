/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:55 by chughes           #+#    #+#             */
/*   Updated: 2023/01/14 16:29:57 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Renders next frame from map to window
int	render_frame(void)
{
	t_data	*data;
	int		x;
	int		y;

	data = get_data();
	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
			put_tile(data->map[y][x], x * 64, y * 64);
	}
	put_tile('P', data->x_p * 64, data->y_p * 64);
	return (0);
}
