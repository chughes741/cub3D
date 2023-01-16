/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:32:36 by chughes           #+#    #+#             */
/*   Updated: 2023/01/16 15:39:41 by chughes          ###   ########.fr       */
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

# define WIDTH 1200
# define HEIGHT 900

// Enum for key codes
enum {
	W_KEY = 13,
	A_KEY = 0,
	S_KEY = 1,
	D_KEY = 2,
	L_KEY = 123,
	R_KEY = 124,
	ESC_KEY = 53
};

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

// Enum for map values
enum {
	EMPTY = 0,
	WALL = 1,
	PLAYER = 2,
	SPACE = 3
};

// Data struct with window data
typedef struct s_data {
	void	*mlx;
	void	*win;
	char	*addr;
	int		endian;
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
	int		floor;
	int		ceiling;
	int		**map;
	int		width;
	int		height;
}			t_data;

// Libft functions
void	*xalloc(size_t nitems, size_t size);
void	*xfree(void *ptr);
char	*gnl(int fd);
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
void	get_size(void);
void	exit_error(void);

// MLX interop functions
void	close_window(t_data **data);
int		render_frame(void);
void	put_tile(char tile, int x, int y);
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
