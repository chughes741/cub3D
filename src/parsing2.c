/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:29:23 by chughes           #+#    #+#             */
/*   Updated: 2023/01/23 15:49:25 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Reads map file into an array of strings
void	read_map(char *map_name)
{
	t_data	*d;
	char	*line;
	int		map_fd;

	d = get_data();
	map_fd = open(map_name, O_RDONLY);
	if (map_fd == -1)
		exit_error("could not open map file ");
	line = gnl(map_fd);
	while (line)
	{
		d->map_file = array_realloc(d->map_file, arraylen(d->map_file) + 1);
		d->map_file[arraylen(d->map_file)] = line;
		line = gnl(map_fd);
	}
	close(map_fd);
	return ;
}

// Parses map_file into textures, colours, and int array
void	parse_map(void)
{
	t_data	*data;

	data = get_data();
	grab_textures();
	grab_colors();
	grab_map();
	return ;
}

// Removes texture lines from map_file
void	grab_textures(void)
{
	t_data	*d;
	int		i;

	d = get_data();
	i = 0;
	while (d->map_file[i])
	{
		if (ft_strncmp(d->map_file[i], "NO ", 3) == 0)
		{
			d->tex_path[NORTH] = strpop(ft_strdup(d->map_file[i] + 3), -1);
			d->map_file = array_del_one(d->map_file, i);
			--i;
		}
		else if (ft_strncmp(d->map_file[i], "SO ", 3) == 0)
		{
			d->tex_path[SOUTH] = strpop(ft_strdup(d->map_file[i] + 3), -1);
			d->map_file = array_del_one(d->map_file, i);
			--i;
		}
		else if (ft_strncmp(d->map_file[i], "WE ", 3) == 0)
		{
			d->tex_path[WEST] = strpop(ft_strdup(d->map_file[i] + 3), -1);
			d->map_file = array_del_one(d->map_file, i);
			--i;
		}
		else if (ft_strncmp(d->map_file[i], "EA ", 3) == 0)
		{
			d->tex_path[EAST] = strpop(ft_strdup(d->map_file[i] + 3), -1);
			d->map_file = array_del_one(d->map_file, i);
			--i;
		}
		++i;
	}
}

// Removed color lines from map_file
void	grab_colors(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	while (data->map_file[i])
	{
		if (ft_strncmp(data->map_file[i], "F ", 2) == 0
			&& data->floor_name == NULL)
		{
			data->floor_name = ft_strdup(data->map_file[i] + 3);
			data->map_file = array_del_one(data->map_file, i);
			--i;
		}
		if (ft_strncmp(data->map_file[i], "C ", 2) == 0
			&& data->ceiling_name == NULL)
		{
			data->ceiling_name = ft_strdup(data->map_file[i] + 3);
			data->map_file = array_del_one(data->map_file, i);
			--i;
		}
		++i;
	}
	set_colors();
}

// Sets floor and ceiling colors
void	set_colors(void)
{
	t_data	*data;
	char	**floor;
	char	**ceiling;
	int		i;

	data = get_data();
	floor = ft_split(data->floor_name, ',');
	ceiling = ft_split(data->ceiling_name, ',');
	i = -1;
	while (floor[++i])
		data->floor |= ft_atoi(floor[i]) << (24 - i * 8);
	i = -1;
	while (ceiling[++i])
		data->ceiling |= ft_atoi(ceiling[i]) << (24 - i * 8);
}
