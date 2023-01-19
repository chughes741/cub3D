/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:47:02 by minkim            #+#    #+#             */
/*   Updated: 2023/01/18 20:01:06 by minkim           ###   ########.fr       */
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
	if (flag == 0 || flag > 1)
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

int flood_fill(int x, int y)
{
	t_data	*data;
	
	data = get_data();
	if (data->map[x][y] == 0)
	{
		data->map[x][y] = 4;
		flood_fill(x+1, y);
		flood_fill(x, y+1);
		flood_fill(x-1, y);
		flood_fill(x, y-1);
	}
	return (0);
}

// Check if the map is properly closed
int check_closed(void)
{
	t_data	*data;

	data = get_data();
	data->map[(int)data->pos_x][(int)data->pos_y] = 0;
	return flood_fill(data->pos_x, data->pos_y);
}

int check_multi(void)
{
	t_data	*data;

	data = get_data();
	return (0);
}

// Check if the map is valid
void check_map(void)
{
	t_data	*data;

	data = get_data();
	if (check_player())
		exit_error();
	if (check_space())
		exit_error();
	// if (check_closed())
	// 	exit_error();
	// check_multi();
    
	return ;
}
