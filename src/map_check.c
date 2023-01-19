/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:47:02 by minkim            #+#    #+#             */
/*   Updated: 2023/01/19 17:26:02 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Check if there is only one player point
int check_player(void)
{
	t_data	*data;
	int		i;
	int		j;
	int		flag;

	data = get_data();
	flag = 0;
	i = 0;
	while (data->map_file[i])
	{
		j = 0;
		while (data->map_file[i][j])
		{
			if (ft_strchr("NESW", data->map_file[i][j]) != NULL)
				flag++;
			j++;
		}
		i++;
	}
	if (flag != 1)
		return (1);
	return (0);
}

// Check if there is a character which is not allowed
int check_space(void)
{
	t_data	*data;
	int		i;
	int		j;
	int		flag0;
	int		flag1;

	data = get_data();
	i = 0;
	flag0 = 0;
	flag1 = 0;
	while (data->map_file[i])
	{
		j = 0;
		while (data->map_file[i][j])
		{
			if (ft_strchr("\n01 NESW", data->map_file[i][j]) == NULL)
				 return (1);
			if (data->map_file[i][j] == '0')
				flag0++;
			if (data->map_file[i][j] == '1')
				flag1++;
			j++;
		}
		i++;
	}
	if (flag0 < 1 || flag1 < 10)
		return (1);
	return (0);
}

int flood_fill_player(int x, int y)
{
	t_data	*data;
	
	data = get_data();
	if (x >= data->height || data->map_file[x][y] == '\n')
		exit_error();
	if (data->map_file[x][y] == '0')
	{
		data->map_file[x][y] = '=';
		flood_fill_player(x+1, y);
		flood_fill_player(x, y+1);
		flood_fill_player(x-1, y);
		flood_fill_player(x, y-1);
	}
	return (0);
}

// Check if the map is properly closed
int check_closed_player(void)
{
	t_data	*data;

	data = get_data();
	data->map_file[(int)data->pos_x][(int)data->pos_y] = '0';
	return flood_fill_player(data->pos_x, data->pos_y);
}

int flood_fill_first_zero(int x, int y)
{
	t_data	*data;
	
	data = get_data();
	// if (x == 0 || y == 0)
	// 	exit_error();
	if (x >= data->height || data->map_file[x][y] == '\n' || data->map_file[x][y] == ' ')
		exit_error();
	if (data->map_file[x][y] == '0')
	{
		data->map_file[x][y] = '=';
		flood_fill_first_zero(x+1, y);
		flood_fill_first_zero(x, y+1);
		flood_fill_first_zero(x-1, y);
		flood_fill_first_zero(x, y-1);
	}
	return (0);
}

int	check_surround_first_zero(int i, int j)
{
	t_data	*data;
	
	data = get_data();
	if (i < 1 || j < 1)
		exit_error();
	if (data->map_file[i][j-1] == ' ')
		exit_error();
	if (data->map_file[i-1][j-1] == '1' && \
		data->map_file[i-1][j] == '1' && data->map_file[i][j-1] == '1')
		return (0);
	else
		exit_error();
	return (1);
}


int	check_closed_first_zero(void)
{
	t_data	*data;
	int		i;
	int		j;

	data = get_data();
	i = 0;
	while (data->map_file[i])
	{
		j = 0;
		while (data->map_file[i][j])
		{
			if (data->map_file[i][j] == '0')
			{
				if (check_surround_first_zero(i, j))
					return (0);
				return flood_fill_first_zero(i, j);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void check_surround_last_row(int i, int j)
{
	t_data	*data;
	
	data = get_data();
	if (data->map_file[i-1][j] != '1' || data->map_file[i][j+1] != '1')
		exit_error();
}

int	check_surround_last_one(int i, int j)
{
	t_data	*data;
	
	data = get_data();
	if (data->map_file[i-1][j] != '1' || data->map_file[i][j-1] != '1')
		exit_error();
	return (0);
}

int	check_last_row(void)
{
	t_data	*data;
	int		i;
	int		flag;

	data = get_data();
	flag = 0;
	i = 0;
	while (data->map_file[data->height-1][i])
	{
		if (ft_strchr("1 ", data->map_file[data->height-1][i]) == NULL)
			exit_error();
		if (flag == 0 && data->map_file[data->height-1][i] == '1')
		{
			check_surround_last_row(data->height-1, i);
			flag = 1;
		}
		i++;
	}
	while (data->map_file[data->height-1][--i])
	{
		if (data->map_file[data->height-2][i] && data->map_file[data->height-2][i] != '\n' && data->map_file[data->height-1][i] == '1')
			return check_surround_last_one(data->height-1, i);
	}
	return (0);
}

int	check_surround_first_one(int i, int j)
{
	t_data	*data;
	
	data = get_data();
	if (data->map_file[i+1][j] != '1' || data->map_file[i][j-1] != '1')
		exit_error();
	return (0);
}

int	check_first_row(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	while (data->map_file[0][i] != '\n')
	{
		if (ft_strchr("1 ", data->map_file[0][i]) == NULL)
			exit_error();
		i++;
	}
	return (0);
}

int	check_left(void)
{
	t_data	*data;
	int		i;
	int		j;

	data = get_data();
	i = 0;
	while (data->map_file[i])
	{
		j = 0;
		while (data->map_file[i][j])
		{
			while (data->map_file[i][j] == ' ')
				j++;
			if (data->map_file[i][j] == '1')
				break ;
			else
				exit_error();
			j++;
		}
		i++;
	}
	return (0);
}

int	check_right(void)
{
	t_data	*data;
	int		i;
	int		j;

	data = get_data();
	i = 0;
	while (data->map_file[i])
	{
		j = 0;
		while (data->map_file[i][j])
		{
			if (data->map_file[i][j] == '\n')
			{
				while (data->map_file[i][--j] == ' ')
					;
				if (data->map_file[i][j] == '1')
					break ;
				else
					exit_error();
			}
			j++;
		}
		i++;
	}
	return (0);
}

// Check if the map is valid
void check_map(void)
{
	t_data	*data;

	data = get_data();
	if (check_first_row())
		exit_error();
	if (check_last_row())
		exit_error();
	if (check_left())
		exit_error();
	if (check_right())
		exit_error();
	if (check_player())
		exit_error();
	if (check_space())
		exit_error();
	if (check_closed_player())
		exit_error();
	if (check_closed_first_zero())
		exit_error();
	return ;
}
