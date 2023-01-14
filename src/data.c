/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:19 by chughes           #+#    #+#             */
/*   Updated: 2023/01/14 16:59:15 by chughes          ###   ########.fr       */
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
	t_data	*d;
	int		w;
	int		h;

	d = get_data();
	d->map_name = argv[1];
	check_input(argc);
	d->mlx = mlx_init();
	d->east = mlx_xpm_file_to_image(d->mlx, "./assets/textures/east_texture.xpm", &w, &h);
	d->west = mlx_xpm_file_to_image(d->mlx, "./assets/textures/west_texture.xpm", &w, &h);
	d->north = mlx_xpm_file_to_image(d->mlx, "./assets/textures/north_texture.xpm", &w, &h);
	d->south = mlx_xpm_file_to_image(d->mlx, "./assets/textures/south_texture.xpm", &w, &h);
	return ;
}

// Frees data and its contents
void	del_data(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = -1;
	if (data->map)
	{
		while (data->map[++i])
			data->map[i] = xfree(data->map[i]);
		data->map = xfree(data->map);
	}
	data = xfree(data);
	return ;
}
