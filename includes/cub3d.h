/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:05:21 by vihane            #+#    #+#             */
/*   Updated: 2025/07/08 19:54:36 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <float.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define ERR_ARG "Error\nUsage: ./cub3d <map.cub>\n"
# define ERR_CUB "Error\nInvalid file extension. Expected .cub\n"
# define ERR_MLX "Error\nFailed to initialize mlx\n"
# define ERR_WIN "Error\nFailed to create window\n"
# define ERR_IMG "Error\nFailed to create image\n"
# define ERR_XPM_IMG "Error\nFailed to create mlx image\n"
# define ERR_IMG_ADDR "Error\nFailed to get image address\n"
# define ERR_NO_MAP "Error\nMissing map\n"
# define ERR_MAP "Error\nInvalid map\n"
# define ERR_MAP_INIT "Error\nFailed to initialize map\n"
# define ERR_MALLOC "Error\nMemory allocation failed\n"
# define ERR_STRDUP "Error\nFailed to duplicate string\n"
# define ERR_FILE "Error\nFile not found\n"
# define ERR_COLOR "Error\nInvalid color: expect (R,G,B) in range [0,255]\n"
# define ERR_DUP_COLOR "Error\nDuplicate color\n"
# define ERR_TEXTURE "Error\nInvalid texture path\n"
# define ERR_PLAYER "Error\nInvalid player position\n"
# define ERR_NO_TEXTURE "Error\nMissing texture\n"
# define ERR_TEXTURE_ADDR "Error\nFailed to get texture address\n"
# define ERR_DUP_TEXTURE "Error\nDuplicate texture\n"
# define ERR_NO_PLAYER "Error\nMissing player position\n"
# define ERR_NO_FLOOR "Error\nMissing floor color\n"
# define ERR_NO_CEILING "Error\nMissing ceiling color\n"
# define ERR_XPM "Error\nInvalid texture file format. Expected .xpm\n"
# define ERR_CLOSE_MAP "Error\nMap must be closed by walls\n"
# define ERR_DUP_PLAYER "Error: Duplicate player position detected\n"
# define ERR_GNL "Error\nFailed to read line from file\n"
# define ERR_IMG_INIT "Error\nImage not initialized.\n"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364

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
}				t_keys;

/*TYPES ENUM*/
typedef enum e_event_type
{
	KEY_PRESS = 2,
	KEY_RELEASE = 3,
	DESTROY_NOTIFY = 17,
}				t_event_type;

/*MASKS ENUM*/
typedef enum e_event_mask
{
	KEYPRESSMASK = 1,
	KEYRELEASEMASK = 2,
	STRUCNOTIFYMASK = 131072,
}				t_event_mask;

typedef struct s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct s_player
{
	t_point		dir;
	t_point		pos;
	t_point		mouse_pos;
	t_point plane; // champ de vision du player
	double		angle;
	double		speed;
	int			move_up;
	int			move_down;
	int			move_left;
	int			move_right;
	int			turn_left;
	int			turn_right;
}				t_player;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_img
{
	void		*mlx_img;
	char *data;    // adresse brut de l'image (utile ?)
	char *addr;    // pointeur vers les pixels (image buffer)
	int bpp;       // bits par pixel (32)
	int width;     // largeur de l'image en pixels
	int height;    // hauteur de l'image en pixels
	int line_size; // nb d'octets par ligne de l'image
	int endian;    // ordre des octets (couleurs)
}				t_img;

typedef struct s_ray
{
	int map_x; // case actuelle du rayon dans la grille
	int			map_y;
	int step_x;       // direction a prendre (+1 ou -1) en X
	int step_y;       // same en Y
	int wall_side;    // 0 si mur X touche, 1 si mur Y
	double cam_x;     // coordonnee "camera" pour ce rayon
	double step;      // pas pour le sampling vertical de la texture
	double tex_pos;   // position verticale actuelle dans la texture
	double ray_dir_x; // direction du rayon en X
	double		ray_dir_y;
	double		delta_dist_x;
	// distance entre 2 lignes de grille sur X = distance pour traverser une case en X (horizontalement)
	double		delta_dist_y;
	double side_dist_x; // distance restante jusqu'a la prochaine case X
	double		side_dist_y;
	double		perp_wall_dist;
	// distance perpendiculaire entre le joueur et le mur (pour corriger le fish-eye distortion)
	double wall_x; // position precise ou le rayon touche le mur
	int			tex_x;
	// colonne precise de la texture choisie pour le rayon actuel
	int			tex_y;
}				t_ray;

typedef struct s_cub3d
{
	char		*line;
	int			fd;
	int			i;
	int			j;
	char		**map;
	void		*mlx_ptr;
	void		*win_ptr;
	t_player	player;
	t_img		image;
	t_img		minimap;
	t_img		minimap_player;
	t_img		texture_north;
	t_img		texture_south;
	t_img		texture_west;
	t_img		texture_east;
	t_color		floor;
	t_color		ceiling;
	t_color		rgb;
	t_ray ray;      // pointeur ou pas ?
	int map_start;  // ligne a partir de laquelle commence la map
	int *map_width; // largeur de la map (en cases)
	int map_height; // hauteur de la map (en cases)
	int win_width;  // taille de la fenetre en pixels
	int			win_height;
	int map_view;      // 0 si on affiche la map, 1 si on affiche les textures
	int textture_view; // 0 si on affiche la map, 1 si on affiche les textures
}				t_cub3d;

/*FUNCTIONS*/

int				close_game(void *param, char *msg);
void			free_map(t_cub3d *cub3d);
void			free_double_array(char ***array);

void			check_color(t_cub3d *cub3d, t_color *color, char *line);

int				keypress(int keycode, t_cub3d *cub3d);

int				main(int argc, char **argv);
void			simple_exit(char *msg);

void			map_height_size(t_cub3d *cub3d, int fd, int n);
void			add_map_line(t_cub3d *cub3d, char *line);
void			init_map(t_cub3d *cub3d, char *file, int n);
void			keep_map(t_cub3d *cub3d, char *file, char *line, int n);

void			check_map_texture_and_color(t_cub3d *cub3d);
int				map_texture_and_color(t_cub3d *cub3d, char *line);
int				parse_map_first(t_cub3d *cub3d, char *file);

void			check_map_inside(t_cub3d *cub3d, char c, int i, int j);
void			check_space(t_cub3d *cub3d, int i, int j);
void			parse_map_second(t_cub3d *cub3d);

void			check_texture(t_cub3d *cub3d, char *line);

int				ft_isin(char c, char *str);
int				is_null(char **map, int i, int j);
int				line_is_empty(t_cub3d *cub3d, char *line);
int				handle_coma(char *str);

void			ft_free_split(char **split);

// INIT

void			init_mlx(t_cub3d *cub3d);
void			init_data(t_cub3d *cub3d);
void			init_texture(t_cub3d *cub3d);
void			init_player(t_cub3d *cub3d);
void			init_image(t_img *img, char *line, t_cub3d cub3d);

// RAYCASTING

void			get_delta_distance(t_ray *ray);
void			setup_dda_steps(t_cub3d *cub);
void			digital_differential_analyser(t_cub3d *cub);
void			init_raycasting(t_cub3d *cub, int x);
void			raycasting(t_cub3d *cub);

void	draw_pixel(t_cub3d *cub, t_point p, int color);
void			calculate_wall_slice(t_cub3d *cub, int *line_height, int *start,
					int *end);
void			calculate_tex_mapping(t_cub3d *cub, int start, int line_height);
void			draw_wall_pixel(t_cub3d *cub, t_point pos, int texture);
void			draw_wall_column(t_cub3d *cub, int x);

int				create_trgb(int t, t_color color);
void			render_background(t_cub3d *cub);
int				render_3D_scene(void *param);

int				get_color(t_cub3d *cub, int x, int y, int i);

// GAMEPLAY

int				keypress(int keycode, t_cub3d *cub3d);
int				close_window(t_cub3d *cub3d);
void			player_move(t_cub3d *cub, double dx, double dy, char sign);
void			player_rotate(t_cub3d *cub, double angle);
int				init_game(t_cub3d *cub);
int				line_is_empty(t_cub3d *cub3d, char *line);

void			put_img_to_window(t_cub3d *cub3d);

#endif