/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:32:36 by chughes           #+#    #+#             */
/*   Updated: 2023/01/18 13:27:14 by chughes          ###   ########.fr       */
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

# include "cub3D_defines.h"

// Data struct with window data
typedef struct s_data {
	// MLX
	void	*mlx;
	void	*win;
	char	*addr;
	int		endian;
	void	*img;
	int		bpp;
	int		line_size;

	// Map and textures
	char	**map_file;
	char	*east_name;
	char	*west_name;
	char	*north_name;
	char	*south_name;
	char	*floor_name;
	char	*ceiling_name;

	void	*east;
	void	*west;
	void	*north;
	void	*south;
	color_t	floor;
	color_t	ceiling;
	int		width;
	int		height;
	int		**map;

	// Camera info
	coord_t	pos;
	double	pos_x;
	double	pos_y;
	coord_t	dir;
	double	dir_x;
	double	dir_y;
	coord_t	plane;
	double	plane_x;
	double	plane_y;

	// Frame info
	double	time;
	double	old_time;
}			t_data;

// Libft functions
void	*xalloc(size_t nitems, size_t size);
void	*xfree(void *ptr);
char	*gnl(int fd);
int		ft_atoi(const char *str);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *str);
int		ft_linelen(const char *str);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*str_append(char *s1, char *s2);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		arraylen(char **array);
char	**arraydup(char **array);
char	**array_realloc(char **ptr, int size);
char	**array_del_one(char **array, int position);
char	**free_array(char **array);
char	**ft_split(char const *s, char c);

// Data setup and teardown functions
t_data	*get_data(void);
void	init_data(int argc, char *argv[]);
void	del_data(void);

// Map parsing checks
void	check_input(int argc, char *path);
void	read_map(char *map_name);
void	parse_map(void);
void	grab_textures(void);
void	grab_colors(void);
void	grab_map(void);
void	copy_map(void);
void	init_player(char direction, int x, int y);
void	get_size(void);
void	set_colors(void);
void	exit_error(void);

// MLX interop functions
void	close_window(t_data **data);
int		render_frame(void);
int		exit_window(int keycode, t_data **data);
void	close_window(t_data **data);
int		keydown(int keycode, t_data **data);

// Movement functions
void	move_north(t_data **data);
void	move_west(t_data **data);
void	move_south(t_data **data);
void	move_east(t_data **data);
void	look_left(t_data **data);
void	look_right(t_data **data);

#endif // CUB3D_H
