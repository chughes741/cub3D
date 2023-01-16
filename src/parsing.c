/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:46 by chughes           #+#    #+#             */
/*   Updated: 2023/01/16 12:57:00 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Reads map file into an array of strings
void	parse_map(void)
{
	t_data	*data;

	return ; // RBS

	data = get_data();
	data->map_fd = open(data->map_name, O_RDONLY);
	data->map = xalloc(data->height + 1, sizeof(char *));
	close(data->map_fd);
	return ;
}

// Checks input and sets map height
void	check_input(int argc)
{
	t_data	*data;

	data = get_data();
	if (argc != 2)
		; // exit_error();
	return ; // RBS
	// if (ft_strncmp(&(data->map_name)[ft_strlen(data->map_name) - 4], ".cub", 4))
		// exit_error();
	parse_map();
	return ;
}
