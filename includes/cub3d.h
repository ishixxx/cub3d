/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:05:21 by vihane            #+#    #+#             */
/*   Updated: 2025/06/11 23:18:03 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../minilibx-linux-master/mlx.h"
# include "X11/keysym.h"
# include "X11/keysymdef.h"

# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define ERR_ARG "Error\nUsage: ./cub3d <map.cub>\n"
# define ERR_CUB "Error\nInvalid file extension. Expected .cub\n"
# define ERR_MLX "Error\nFailed to initialize mlx\n"
# define ERR_WIN "Error\nFailed to create window\n"
# define ERR_IMG "Error\nFailed to create image\n"
# define ERR_MAP "Error\nInvalid map\n"
# define ERR_MALLOC "Error\nMemory allocation failed\n"
# define ERR_COLOR "Error\nInvalid color\n"
# define ERR_TEXTURE "Error\nInvalid texture path\n"
# define ERR_PLAYER "Error\nInvalid player position\n"
# define ERR_NO_TEXTURE "Error\nMissing texture\n"
# define ERR_NO_MAP "Error\nMissing map\n"
# define ERR_NO_PLAYER "Error\nMissing player position\n"
# define ERR_NO_FLOOR "Error\nMissing floor color\n"
# define ERR_NO_CEILING "Error\nMissing ceiling color\n"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

typedef enum e_keys
{
	ESC = 65307,
	UP_ARROW = 65362,
	DOWN_ARROW = 65364,
	LEFT_ARROW = 65361,
	RIGHT_ARROW = 65363,
    W_KEY = 119,
    A_KEY = 97,
    D_KEY = 100,
    S_KEY = 115,
    E_KEY = 101,
}					t_keys;

/*TYPES ENUM*/
typedef enum e_event_type
{
	KEY_PRESS = 2,
	KEY_RELEASE = 3,
	DESTROY_NOTIFY = 17,
}					t_event_type;

/*MASKS ENUM*/
typedef enum e_event_mask
{
	KEYPRESSMASK = 1,
	KEYRELEASEMASK = 2,
	STRUCNOTIFYMASK = 131072,
}					t_event_mask;

typedef struct s_point
{
	int		x;
	int		y;
}					t_point;

typedef struct s_player
{
	t_point *dir;
	t_point *pos;
	t_point *mouse_pos;
	int		move_up;
	int		move_down;
	int		move_left;
	int		move_right;
	int		turn_left;
	int		turn_right;
}					t_player;

typedef struct s_color
{
	int floor;
	int ceiling;
} 				t_color;

typedef struct s_img
{
	char 	*path;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int 	width;
	int		height;
	int		line_length;
	int		endian;
}					t_img;

typedef struct s_cub3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_player	*player;
	t_img		*north;
	t_img		*south;
	t_img		*west;
	t_img		*east;
	char		**map;
	int			map_start;
	int			map_width;
	int			map_height;
}					t_cub3d;

/*FUNCTIONS*/

int main(int argc, char **argv);
void data_init(int argc, char **argv, t_cub3d *cub3d);

#endif