/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:46 by chughes           #+#    #+#             */
/*   Updated: 2023/01/16 15:31:34 by chughes          ###   ########.fr       */
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
		exit_error();
	line = gnl(map_fd);
	while (line)
	{
		d->map_file = array_realloc(d->map_file, arraylen(d->map_file) + 1);
		d->map_file[arraylen(d->map_file) - 1] = line;
		line = gnl(map_fd);
	}
	close(map_fd);
	return ;
}

// Parses map_file into textures, colours, and int array
void parse_map(void)
{
	t_data	*data;

	data = get_data();
	grab_textures();
	grab_colors();
	grab_map();
	return ;
}

// Removes texture lines from map_file
void grab_textures(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	while (data->map_file[i])
	{
		if (ft_strncmp(data->map_file[i], "NO ", 3) == 0 && data->north_name == NULL)
		{
			data->north_name = ft_strdup(data->map_file[i] + 4);
			data->map_file = array_del_one(data->map_file, i);
			--i;
		}
		if (ft_strncmp(data->map_file[i], "SO ", 3) == 0 && data->south_name == NULL)
		{
			data->south_name = ft_strdup(data->map_file[i] + 4);
			data->map_file = array_del_one(data->map_file, i);	
			--i;
		}
		if (ft_strncmp(data->map_file[i], "WE ", 3) == 0 && data->west_name == NULL)
		{
			data->west_name = ft_strdup(data->map_file[i] + 4);
			data->map_file = array_del_one(data->map_file, i);	
			--i;
		}
		if (ft_strncmp(data->map_file[i], "EA ", 3) == 0 && data->east_name == NULL)
		{
			data->east_name = ft_strdup(data->map_file[i] + 4);
			data->map_file = array_del_one(data->map_file, i);	
			--i;
		}
		++i;
	}
}

// Removed color lines from map_file
void grab_colors(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	while (data->map_file[i])
	{
		if (ft_strncmp(data->map_file[i], "F ", 2) == 0 && data->floor_name == NULL)
		{
			data->floor_name = ft_strdup(data->map_file[i] + 3);
			data->map_file = array_del_one(data->map_file, i);
			--i;
		}
		if (ft_strncmp(data->map_file[i], "C ", 2) == 0 && data->ceiling_name == NULL)
		{
			data->ceiling_name = ft_strdup(data->map_file[i] + 3);
			data->map_file = array_del_one(data->map_file, i);
			--i;
		}
		++i;
	}
}

// Moves map tiles from map_file to map
void grab_map(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	while (data->map_file[i])
	{
		if (ft_strchr("1 ", data->map_file[i][0]) != 0)
			exit_error();
	}
	get_size();
	data->map = xalloc(data->height + 1, sizeof(int *));
	i = 0;
	while (i <= data->height)
		data->map[i] = xalloc(data->width + 1, sizeof(int));
	copy_map();
}

// Copies values from map_file to map
void copy_map(void)
{
	t_data	*data;
	int		i;
	int		j;

	data = get_data();
	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (data->map_file[i][j] && j < data->width)
		{
			if (data->map_file[i][j] == ' ')
				data->map[i][j] = SPACE;
			else if (data->map_file[i][j] == '0')
				data->map[i][j] = EMPTY;
			else if (data->map_file[i][j] == '1')
				data->map[i][j] = WALL;
			else if (ft_strchr("NESW", data->map_file[i][j]))
				data->map[i][j] = PLAYER;
			else
				exit_error();
			++j;
		}
		++i;
	}
}

// Gets height and width from map
void get_size(void)
{
	t_data	*data;

	data = get_data();
	data->height = 0;
	data->width = 0;
	while (data->map_file[data->height])
	{
		if (ft_linelen(data->map_file[data->height]) > data->width)
			data->width = ft_linelen(data->map_file[data->height]);
		++data->height;
	}	
}

// Checks input and sets map_file height
void	check_input(int argc, char *path)
{
	t_data	*data;

	data = get_data();
	if (argc != 2)
		exit_error();
	if (ft_strncmp(&path[ft_strlen(path) - 5], ".cub", 4))
		;
		// exit_error();
	return ;
}
