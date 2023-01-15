/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:46 by chughes           #+#    #+#             */
/*   Updated: 2023/01/15 10:24:34 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Reads map file into an array of strings
void	parse_map(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	data->map_fd = open(data->map_name, O_RDONLY);
	data->map = xalloc(data->height + 1, sizeof(char *));
	i = -1;
	while (++i < data->height)
		data->map[i] = gnl(data->map_fd);
	data->width = ft_linelen(data->map[0]);
	close(data->map_fd);
	return ;
}

// Checks input and sets map height
void	check_input(int argc)
{
	t_data	*data;

	data = get_data();
	if (argc != 2)
		exit_error();
	if (ft_strncmp(&(data->map_name)[ft_strlen(data->map_name) - 4], ".cub", 4))
		exit_error();
	map_height();
	parse_map();
	check_map();
	if (data->n_col < 1 || data->n_ex < 1 || data->n_p != 1)
		exit_error();
	check_walls(data);
	return ;
}
