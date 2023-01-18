/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:17:58 by chughes           #+#    #+#             */
/*   Updated: 2023/01/18 13:57:00 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_DEFINES_H
# define CUB3D_DEFINES_H

# define WIDTH 1200
# define HEIGHT 900
# define ROT_SPEED 0.1
# define MOVE_SPEED 0.1
# define Y 0
# define X 1

// coord_t[0] = y, coord_t[1] = x
typedef double[2]	coord_t;
typedef int[2]		pair_t;
typedef int			colour_t;

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

#endif // CUB3D_DEFINES_H
