/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:39:41 by chughes           #+#    #+#             */
/*   Updated: 2023/01/30 14:33:31 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Just here for norm
void	set_texture(int *i, int side)
{
	t_data	*data;
	int		index;

	data = get_data();
	if (data->tex_path[side])
		exit_error("too many texture paths in map file");
	data->tex_path[side] = strpop(ft_strdup(data->map_file[*i] + 3), -1);
	index = 0;
	while (data->tex_path[side][0] == ' ')
		data->tex_path[side] = strpop(data->tex_path[side], 0);
	data->map_file = array_del_one(data->map_file, *i);
	--(*i);
}
