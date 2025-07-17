/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:05:21 by vihane            #+#    #+#             */
/*   Updated: 2025/07/17 17:46:28 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include "define.h"
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
	t_point		plane;
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
	char		*data;
	char		*addr;
	int			bpp;
	int			width;
	int			height;
	int			line_size;
	int			endian;
}				t_img;

typedef struct s_ray
{
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			wall_side;
	double		cam_x;
	double		step;
	double		tex_pos;
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_wall_dist;
	double		wall_x;
	int			tex_x;
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
	t_ray		ray;
	int			map_start;
	int			*map_width;
	int			map_height;
	int			win_width;
	int			win_height;
}				t_cub3d;

/*FUNCTIONS*/

int				close_game(t_cub3d *cub3d, char *msg);
void			free_map(t_cub3d *cub3d);
void			free_double_array(char ***array);
void			free_mlx(t_cub3d *cub3d);
void			free_cub(t_cub3d *cub3d);

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
void			parse_map_first(t_cub3d *cub3d, char *file);

void			check_map_inside(t_cub3d *cub3d, char c, int i, int j);
void			check_space(t_cub3d *cub3d, int i, int j);
void			parse_map_second(t_cub3d *cub3d);
void			set_direction1(t_cub3d *cub3d, char c);
void			set_direction2(t_cub3d *cub3d, char c);

void			check_texture(t_cub3d *cub3d, char *line);

int				ft_isin(char c, char *str);
int				is_null(char **map, int i, int j);
int				line_is_empty(t_cub3d *cub3d, char *line);
int				handle_coma(char *str);

// INIT

void			init_mlx(t_cub3d *cub3d);
void			init_data(t_cub3d *cub3d);
void			init_texture(t_cub3d *cub3d);
void			init_player(t_cub3d *cub3d);

// RAYCASTING

void			get_delta_distance(t_ray *ray);
void			setup_dda_steps(t_cub3d *cub);
void			digital_differential_analyser(t_cub3d *cub);
void			init_raycasting(t_cub3d *cub, int x);
void			raycasting(t_cub3d *cub);

void			draw_pixel(t_cub3d *cub, t_point p, int color);
void			calculate_wall_slice(t_cub3d *cub, int *line_height, int *start,
					int *end);
void			calculate_tex_mapping(t_cub3d *cub, int start, int line_height);
void			draw_wall_pixel(t_cub3d *cub, t_point pos, int texture);
void			draw_wall_column(t_cub3d *cub, int x);

int				create_trgb(int t, t_color color);
void			render_background(t_cub3d *cub);
int				render_scene(t_cub3d *cub);

int				get_color(t_cub3d *cub, int x, int y, int i);
int				get_tex_id(t_cub3d *cub);
int				is_out_of_bounds(t_cub3d *cub);
void			advance_ray(t_cub3d *cub);
int				is_wall(t_cub3d *cub);

// GAMEPLAY

int				keypress(int keycode, t_cub3d *cub3d);
int				close_window(t_cub3d *cub3d);
int				is_position_free(t_cub3d *cub, double x, double y);
void			player_move(t_cub3d *cub, double dx, double dy, char sign);
void			player_rotate(t_cub3d *cub, double angle);
int				init_game(t_cub3d *cub);
int				line_is_empty(t_cub3d *cub3d, char *line);

void			put_img_to_window(t_cub3d *cub3d);

void			draw_minimap_border(t_cub3d *cub3d);
void			draw_minimap_background(t_cub3d *cub3d);
void			draw_minimap_pixel(t_cub3d *cub, int x, int y, int color);
void			draw_minimap_element(t_cub3d *cub3d, int x, int y, int color);
void			draw_player_on_minimap(t_cub3d *cub);

int				get_map_tile_at_position(t_cub3d *cub3d, double map_x,
					double map_y);
void			draw_minimap_pixel_at(t_cub3d *cub3d, int x, int y,
					int tile_type);
void			draw_minimap_line(t_cub3d *cub3d, int y, double player_x,
					double player_y);
void			draw_centered_map(t_cub3d *cub3d, double player_x,
					double player_y);
void			render_minimap(t_cub3d *cub3d);

void			draw_player_at_center(t_cub3d *cub3d);

#endif