/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:19 by chughes           #+#    #+#             */
/*   Updated: 2023/01/16 13:53:50 by chughes          ###   ########.fr       */
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

	d->map = NULL;
	d->north_name = NULL;
	d->south_name = NULL;
	d->east_name = NULL;
	d->west_name = NULL;
	check_input(argc);
	read_map(argv[1]);
	parse_map();
	d->mlx = mlx_init();
	d = get_data();
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
