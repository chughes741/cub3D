/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:32:36 by chughes           #+#    #+#             */
/*   Updated: 2023/01/14 16:23:55 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <OpenGL/gl3.h>
# include <mlx.h>

# include <stdlib.h>	// malloc, free, exit
# include <fcntl.h>		// open
# include <unistd.h>	// close, read
# include <stdio.h>		// printf, perror
# include <string.h>	// strerror

// Enum for MLX functions
enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

// Data struct with window data
typedef struct s_data {
	void	*mlx;
	void	*win;
	char	*addr;
	char	**map;
	char	*map_name;
	int		map_fd;
	int		height;
	int		width;
	int		line_length;
	int		endian;
	int		moves;
	int		x_p;
	int		y_p;
	int		n_col;
	int		n_p;
	int		n_ex;
	void	*wall;
	void	*empty;
	void	*exit;
	void	*collec;
	void	*charac;
}			t_data;

// Data setup and teardown functions
t_data	*get_data(void);
void	init_data(int argc, char *argv[]);
void	del_data(void);

// Map parsing checks
void	check_input(int argc);
void	parse_map(void);
void	exit_error(void);
void	check_map(void);
void	check_tile(void);
void	count_tile(int x, int y);

// MLX interop functions
void	close_window(t_data **data);
int		render_frame(void);
void	put_tile(char tile, int x, int y);
int		exit_window(int keycode, t_data **data);
void	close_window(t_data **data);
int		keydown(int keycode, t_data **data);

// Movement functions
void	move_up(t_data **data);
void	move_dn(t_data **data);
void	move_lf(t_data **data);
void	move_rg(t_data **data);

#endif // CUB3D_H
