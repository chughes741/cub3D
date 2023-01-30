/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:38:59 by chughes           #+#    #+#             */
/*   Updated: 2023/01/30 12:46:59 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Checks that numbers are within 0-255
void	check_numbers(char **floor, char **ceiling)
{
	bool	flag;

	flag = false;
	if (ft_atoi(floor[0]) > 255 || ft_atoi(floor[0]) < 0
		|| ft_atoi(floor[1]) > 255 || ft_atoi(floor[1]) < 0
		|| ft_atoi(floor[2]) > 255 || ft_atoi(floor[2]) < 0
		|| ft_atoi(ceiling[0]) > 255 || ft_atoi(ceiling[0]) < 0
		|| ft_atoi(ceiling[1]) > 255 || ft_atoi(ceiling[1]) < 0
		|| ft_atoi(ceiling[2]) > 255 || ft_atoi(ceiling[2]) < 0)
		flag = true;
	if (flag)
	{
		free_array(floor);
		free_array(ceiling);
		exit_error("with colors");
	}
}
