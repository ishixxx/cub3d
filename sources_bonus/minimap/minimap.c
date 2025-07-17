/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:14:23 by vihane            #+#    #+#             */
/*   Updated: 2025/07/17 17:09:02 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	get_map_tile_at_position(t_cub3d *cub3d, double map_x, double map_y)
{
	int	int_map_x;
	int	int_map_y;

	int_map_x = (int)floor(map_x);
	int_map_y = (int)floor(map_y);
	if (int_map_x >= 0 && int_map_y >= 0 && int_map_y < cub3d->map_height
		&& int_map_x < (int)ft_strlen(cub3d->map[int_map_y]))
	{
		if (cub3d->map[int_map_y][int_map_x] == '1')
			return (1);
		else if (cub3d->map[int_map_y][int_map_x] == '0' || ft_strchr("NSEW",
				cub3d->map[int_map_y][int_map_x]))
			return (0);
	}
	return (-1);
}

void	draw_minimap_pixel_at(t_cub3d *cub3d, int x, int y, int tile_type)
{
	if (tile_type == 1)
		draw_minimap_pixel(cub3d, MINIMAP_X + x, MINIMAP_Y + y, 0x000000);
	else if (tile_type == 0)
		draw_minimap_pixel(cub3d, MINIMAP_X + x, MINIMAP_Y + y, 0xFFFFFF);
}

void	draw_minimap_line(t_cub3d *cub3d, int y, double player_x,
		double player_y)
{
	int		x;
	int		center;
	double	map_x;
	double	map_y;

	center = MINIMAP_SIZE / 2;
	x = 0;
	while (x < MINIMAP_SIZE)
	{
		map_x = player_x + (double)(x - center) / MINIMAP_SCALE;
		map_y = player_y + (double)(y - center) / MINIMAP_SCALE;
		draw_minimap_pixel_at(cub3d, x, y, get_map_tile_at_position(cub3d,
				map_x, map_y));
		x++;
	}
}

// void	draw_minimap_line(t_cub3d *cub3d, int y, double player_x,
// 		double player_y)
// {
// 	int		x;
// 	int		center_x;
// 	int		center_y;
// 	int		tile_type;
// 	double	map_x;
// 	double	map_y;

// 	center_x = MINIMAP_SIZE / 2;
// 	center_y = MINIMAP_SIZE / 2;
// 	x = 0;
// 	while (x < MINIMAP_SIZE)
// 	{
// 		map_x = player_x + (double)(x - center_x) / MINIMAP_SCALE;
// 		map_y = player_y + (double)(y - center_y) / MINIMAP_SCALE;
// 		tile_type = get_map_tile_at_position(cub3d, map_x, map_y);
// 		if (tile_type == 1)
// 			draw_minimap_pixel(cub3d, MINIMAP_X + x, MINIMAP_Y + y, 0x000000);
// 		else if (tile_type == 0)
// 			draw_minimap_pixel(cub3d, MINIMAP_X + x, MINIMAP_Y + y, 0xFFFFFF);
// 		x++;
// 	}
// }

void	draw_centered_map(t_cub3d *cub3d, double player_x, double player_y)
{
	int	y;

	y = 0;
	while (y < MINIMAP_SIZE)
	{
		draw_minimap_line(cub3d, y, player_x, player_y);
		y++;
	}
}

void	render_minimap(t_cub3d *cub3d)
{
	double	player_x;
	double	player_y;

	player_x = cub3d->player.pos.x;
	player_y = cub3d->player.pos.y;
	draw_minimap_background(cub3d);
	draw_centered_map(cub3d, player_x, player_y);
	draw_minimap_border(cub3d);
	draw_player_at_center(cub3d);
}
