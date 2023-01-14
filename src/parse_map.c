/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:46 by chughes           #+#    #+#             */
/*   Updated: 2023/01/14 16:51:50 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Finds number of rows in map file
void	map_height(void)
{
	t_data	*data;
	char	*temp;

	data = get_data();
	data->map_fd = open(data->map_name, O_RDONLY);
	if (data->map_fd < 0)
		exit_error();
	temp = gnl(data->map_fd);
	while (temp)
	{
		data->height += 1;
		free(temp);
		temp = gnl(data->map_fd);
	}
	close(data->map_fd);
	return ;
}

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

// Checks validity of map
void	check_map(void)
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
			count_tile(x, y);
	}
	return ;
}

// Checks walls
void	check_walls(t_data	*data)
{
	int	i;

	i = -1;
	while (++i < data->width)
	{
		if (data->map[0][i] != '1' || data->map[data->height - 1][i] != '1')
			exit_error();
	}
	i = -1;
	while (++i < data->height)
	{
		if (data->map[i][0] != '1' || data->map[i][data->width - 1] != '1')
			exit_error();
	}
	i = -1;
	while (++i < data->height)
	{
		if (ft_linelen(data->map[i]) != data->width)
			exit_error();
	}
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
