/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:05:21 by vihane            #+#    #+#             */
/*   Updated: 2025/06/29 16:32:01 by vgalmich         ###   ########.fr       */
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
# include <float.h>
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

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

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
	double		x;
	double		y;
}					t_point;

typedef struct s_player
{
	t_point *dir;
	t_point *pos;
	t_point *mouse_pos;
	t_point	*plane; // champ de vision du player
	int		move_up;
	int		move_down;
	int		move_left;
	int		move_right;
	int		turn_left;
	int		turn_right;
}					t_player;

typedef struct s_color
{
	int r;
	int g;
	int	b;
} 				t_color;

typedef struct s_img
{
	char 	*data; // adresse brut de l'image (utile ?)
	char	*addr; // pointeur vers les pixels (image buffer)
	int		bpp; // bits par pixel (32)
	int 	width; // largeur de l'image en pixels
	int		height; // hauteur de l'image en pixels
	int		line_length; // nb d'octets par ligne de l'image
	int		endian; // ordre des octets (couleurs)
}					t_img;

typedef	struct s_ray
{
	int			map_x; // case actuelle du rayon dans la grille
	int			map_y;
	int			step_x; // direction a prendre (+1 ou -1) en X
	int			step_y; // same en Y
	int			wall_side; // 0 si mur X touche, 1 si mur Y
	double		cam_x; // coordonnee "camera" pour ce rayon
	double		step; // pas pour le sampling vertical de la texture
	double		tex_pos; // position verticale actuelle dans la texture
	double		ray_dir_x; // direction du rayon en X
	double		ray_dir_y;
	double		delta_dist_x; // distance entre 2 lignes de grille sur X = distance pour traverser une case en X (horizontalement)
	double		delta_dist_y;
	double		side_dist_x; // distance restante jusqu'a la prochaine case X
	double		side_dist_y;
	double		perp_wall_dist; // distance perpendiculaire entre le joueur et le mur (pour corriger le fish-eye distortion)
	double		wall_x; // position precise ou le rayon touche le mur
	int			tex_x; // colonne precise de la texture choisie pour le rayon actuel
	int			tex_y;
}					t_ray;


typedef struct s_cub3d
{
	char		*line;
	char		**map;
	void		*mlx_ptr;
	void		*win_ptr;
	t_player	player; // structure sur les infos du player
	t_img		image; // structure sur l'image de l'ecran
	t_color		floor; // couleurs de sol et plafond
	t_color		ceiling;
	t_ray		ray; // pointeur ou pas ?
	int			map_start; // ligne a partir de laquelle commence la map
	int			map_width; // largeur de la map (en cases)
	int			map_height; // hauteur de la map (en cases)
	int			win_width; // taille de la fenetre en pixels
	int			win_height;
}					t_cub3d;

/*FUNCTIONS*/

int main(int argc, char **argv);
void data_init(int argc, char **argv, t_cub3d *cub3d);

#endif