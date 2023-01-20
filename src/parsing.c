/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:46 by chughes           #+#    #+#             */
/*   Updated: 2023/01/20 14:10:28 by chughes          ###   ########.fr       */
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
		if (ft_strncmp(data->map_file[i], "NO ", 3) == 0 && data->north_path == NULL)
		{
			data->north_path = ft_strdup(data->map_file[i] + 4);
			data->map_file = array_del_one(data->map_file, i);
			--i;
		}
		else if (ft_strncmp(data->map_file[i], "SO ", 3) == 0 && data->south_path == NULL)
		{
			data->south_path = ft_strdup(data->map_file[i] + 4);
			data->map_file = array_del_one(data->map_file, i);	
			--i;
		}
		else if (ft_strncmp(data->map_file[i], "WE ", 3) == 0 && data->west_path == NULL)
		{
			data->west_path = ft_strdup(data->map_file[i] + 4);
			data->map_file = array_del_one(data->map_file, i);	
			--i;
		}
		else if (ft_strncmp(data->map_file[i], "EA ", 3) == 0 && data->east_path == NULL)
		{
			data->east_path = ft_strdup(data->map_file[i] + 4);
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
	set_colors();
}

// Sets floor and ceiling colors
void set_colors(void)
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

// Moves map tiles from map_file to map
void grab_map(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = -1;
	while (data->map_file[++i])
	{
		if (data->map_file[i][0] == '\n')
		{
			data->map_file = array_del_one(data->map_file, i);
			--i;
		}
		else if (ft_strchr("1 ", data->map_file[i][0]) == NULL)
			exit_error("error reading map ");
	}
	get_size();
	data->map = xalloc(data->height + 1, sizeof(int *));
	i = -1;
	while (++i <= data->height)
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
		while (j < data->width)
		{
			if (j >= ft_linelen(data->map_file[i]) || data->map_file[i][j] == ' ')
				data->map[i][j] = SPACE;
			else if (data->map_file[i][j] == '0')
				data->map[i][j] = EMPTY;
			else if (data->map_file[i][j] == '1')
				data->map[i][j] = WALL;
			else if (ft_strchr("NESW", data->map_file[i][j]) != NULL)
				init_player(data->map_file[i][j], i, j);
			++j;
		}
		++i;
	}
}

// Sets player direction and location
void init_player(char direction, int x, int y)
{
	t_data	*data;

	data = get_data();
	data->pos[X] = x;
	data->pos[Y] = y;
	if (direction == 'N')
		data->dir[X] = -1;
	if (direction == 'E')
		data->dir[Y] = 1;
	if (direction == 'S')
		data->dir[X] = 1;
	if (direction == 'W')
		data->dir[Y] = -1;
}

// Gets height and width from map
void get_size(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	data->height = arraylen(data->map_file);
	data->width = 0;
	i = 0;
	while (i < data->height)
	{
		if (ft_strlen(data->map_file[i]) > (size_t)data->width)
			data->width = ft_strlen(data->map_file[i]) - 1;
		++i;
	}
}

// Checks input and sets map_file height
void	check_input(int argc, char *path)
{
	t_data	*data;

	data = get_data();
	if (argc != 2)
		exit_error("no map path given ");
	if (ft_strlen(path) >= 4 && ft_strncmp(&path[ft_strlen(path) - 4], ".cub", 4))
		exit_error("map does not have correct file suffix ");
	return ;
}
