/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:32:43 by chughes           #+#    #+#             */
/*   Updated: 2023/01/16 15:50:38 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char **argv)
{
	t_data	*d;
	void	*mlx;
	void	*win;

	d = get_data();
	init_data(argc, argv);
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "cub3D");
	mlx_hook(win, ON_DESTROY, 0, exit_window, &d);
	mlx_hook(win, ON_KEYDOWN, 0, keydown, &d);
	mlx_loop_hook(mlx, render_frame, NULL);
	mlx_loop(mlx);
	exit(0);
}
