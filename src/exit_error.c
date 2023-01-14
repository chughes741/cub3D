/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:27 by chughes           #+#    #+#             */
/*   Updated: 2023/01/14 16:29:29 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Called to exit program and display error
void	exit_error(void)
{
	t_data	*data;

	data = get_data();
	del_data();
	perror("Error\n");
	exit(1);
}
