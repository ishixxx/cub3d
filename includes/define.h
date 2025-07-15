/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:03:26 by vihane            #+#    #+#             */
/*   Updated: 2025/07/15 12:29:44 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H   

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
# define ERR_READ "Error\nFailed to read file\n"
# define ERR_OPEN "Error\nFailed to open file\n"
# define INVALID_COLOR_OR_TEXTURE "Error\nInvalid color or texture format\n"

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

# define COLLISION_RADIUS 0.13

# ifndef TEXTURE_WIDTH
#  define TEXTURE_WIDTH 64
# endif

# ifndef TEXTURE_HEIGHT
#  define TEXTURE_HEIGHT 64
# endif

#endif