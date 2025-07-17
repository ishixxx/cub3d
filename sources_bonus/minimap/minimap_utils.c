/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:28:17 by vihane            #+#    #+#             */
/*   Updated: 2025/07/17 16:50:03 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	draw_minimap_border(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < MINIMAP_SIZE)
	{
		draw_minimap_pixel(cub, MINIMAP_X + i, MINIMAP_Y, 0x808080);
		draw_minimap_pixel(cub, MINIMAP_X + i, MINIMAP_Y + MINIMAP_SIZE - 1,
			0x808080);
		i++;
	}
	i = 0;
	while (i < MINIMAP_SIZE)
	{
		draw_minimap_pixel(cub, MINIMAP_X, MINIMAP_Y + i, 0x808080);
		draw_minimap_pixel(cub, MINIMAP_X + MINIMAP_SIZE - 1, MINIMAP_Y + i,
			0x808080);
		i++;
	}
}

void	draw_minimap_background(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			draw_minimap_pixel(cub3d, MINIMAP_X + x, MINIMAP_Y + y, 0x404040);
			x++;
		}
		y++;
	}
}

void	draw_minimap_pixel(t_cub3d *cub, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = cub->image.addr + (y * cub->image.line_size + x * (cub->image.bpp
					/ 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_minimap_element(t_cub3d *cub3d, int x, int y, int color)
{
	int	start_x;
	int	start_y;
	int	i;
	int	j;

	start_x = MINIMAP_X + x * MINIMAP_SCALE;
	start_y = MINIMAP_Y + y * MINIMAP_SCALE;
	j = 0;
	while (j < MINIMAP_SCALE)
	{
		i = 0;
		while (i < MINIMAP_SCALE)
		{
			draw_minimap_pixel(cub3d, start_x + i, start_y + j, color);
			i++;
		}
		j++;
	}
}

void	draw_player_on_minimap(t_cub3d *cub)
{
	int	player_x;
	int	player_y;
	int	i;
	int	j;

	player_x = MINIMAP_X + (int)(cub->player.pos.x * MINIMAP_SCALE);
	player_y = MINIMAP_Y + (int)(cub->player.pos.y * MINIMAP_SCALE);
	j = -2;
	while (j <= 2)
	{
		i = -2;
		while (i <= 2)
		{
			draw_minimap_pixel(cub, player_x + i, player_y + j, 0xFF0000);
			i++;
		}
		j++;
	}
}
