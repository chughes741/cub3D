/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:31:06 by chughes           #+#    #+#             */
/*   Updated: 2023/01/20 13:08:03 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Loads xpm texture into a string of ints
void	load_texture(t_data *data, int *texture, char *path)
{
	t_img	img;
	int		x;
	int		y;

	img.img = mlx_xpm_file_to_image(data->mlx, path, &img.width, &img.height);
	if (img.img == NULL) 
		exit_error("could not load texture");
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.l_size, &img.endian);
	y = -1;
	while (++y < img.height)
	{
		x = -1;
		while (++x < img.width)
			texture[img.width * y + x] = ((int*)img.addr)[img.width * y + x];
	}
	mlx_destroy_image(data->mlx, img.img);
}

// Loads N, E, S, W textures into int*
void	load_textures(t_data *data)
{
	load_texture(data, data->tex[NORTH], "assets/textures/north_texture.xpm");
	load_texture(data, data->tex[EAST], "assets/textures/east_texture.xpm");
	load_texture(data, data->tex[SOUTH], "assets/textures/south_texture.xpm");
	load_texture(data, data->tex[WEST], "assets/textures/west_texture.xpm");
	// load_texture(data, data->tex[NORTH], data->north_path);
	// load_texture(data, data->tex[EAST], data->east_path);
	// load_texture(data, data->tex[SOUTH], data->south_path);
	// load_texture(data, data->tex[WEST], data->west_path);
}
