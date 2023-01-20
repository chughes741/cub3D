/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:19 by chughes           #+#    #+#             */
/*   Updated: 2023/01/20 12:50:13 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Singleton itialization and reference getter
t_data	*get_data(void)
{
	static t_data	*data = NULL;

	if (data == NULL)
		data = xalloc(1, sizeof(t_data));
	return (data);
}

// Initialized data struct
void	init_data(int argc, char *argv[])
{
	t_data	*data;

	data = get_data();
	check_input(argc, argv[1]);
	read_map(argv[1]);
	parse_map();
	data->plane_y = 0.66;
	data->tex = xalloc(4, sizeof(int**));
	data->tex[NORTH] = xalloc(TEX_HEIGHT * TEX_WIDTH, sizeof(int));
	data->tex[EAST] = xalloc(TEX_HEIGHT * TEX_WIDTH, sizeof(int));
	data->tex[SOUTH] = xalloc(TEX_HEIGHT * TEX_WIDTH, sizeof(int));
	data->tex[WEST] = xalloc(TEX_HEIGHT * TEX_WIDTH, sizeof(int));
	load_textures(data);
	return ;
}

// Frees data and its contents
void	del_data(void)
{
	t_data	*data;

	data = get_data();
	data = xfree(data);
	return ;
}
