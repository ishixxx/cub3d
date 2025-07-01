/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:05:21 by vihane            #+#    #+#             */
/*   Updated: 2025/07/01 14:12:26 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "../minilibx-mac-osx/mlx.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
// # include "../minilibx-linux-master/mlx.h"
# include <fcntl.h>
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
# define ERR_COLOR "Error\nInvalid color format: expect (R,G,B) in range [0, 255]\n"
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
	int			x;
	int			y;
}				t_point;

typedef struct s_player
{
	t_point		*dir;
	t_point		*pos;
	t_point		*mouse_pos;
	double		x;
	double		y;
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
	void		*data;
	char		*addr;
	int			bpp;
	int			width;
	int			height;
	int			line_size;
	int			endian;
}				t_img;

typedef struct s_cub3d
{
	char		*line;
	int 		fd;
	int			i;
	int			j;
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
	char		**map;
	int			*map_width;
	int			map_height;
}				t_cub3d;

/*FUNCTIONS*/

void	close_game(t_cub3d *cub3d, char *msg);
void	free_map(t_cub3d *cub3d);
void	free_double_array(char ***array);

void	check_color(t_cub3d *cub3d, t_color *color, char *line);

int				main(int argc, char **argv);

void	map_height_size(t_cub3d *cub3d, int fd, int n);
void	add_map_line(t_cub3d *cub3d, char *line);
void	init_map(t_cub3d *cub3d, char *file, int n);
void	keep_map(t_cub3d *cub3d, char *file, char *line, int n);

void			check_map_texture_and_color(t_cub3d *cub3d);
int	map_texture_and_color(t_cub3d *cub3d, char *line);
int	parse_map_first(int fd, t_cub3d *cub3d, char *file);

void    check_map_inside(t_cub3d *cub3d, char c, int i, int j);
void    check_space(t_cub3d *cub3d, int i, int j);
void    parse_map_second(t_cub3d *cub3d);

char			**read_file(int fd, t_cub3d *cub3d);

void			check_texture(t_cub3d *cub3d, char *line);

int	ft_isin(char c, char *str);
int	is_null(char **map, int i, int j);
void	ignore_space(char **line);
int	line_is_empty(t_cub3d *cub3d, char *line);
int	handle_coma(char *str);

#endif