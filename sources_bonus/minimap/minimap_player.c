/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:51:59 by vihane            #+#    #+#             */
/*   Updated: 2025/07/17 17:09:12 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

// void	draw_player_direction(t_cub3d *cub3d)
// {
// 	int	center_x;
// 	int	center_y;
// 	int	k;
// 	int	line_x;
// 	int	line_y;

// 	center_x = MINIMAP_X + MINIMAP_SIZE / 2;
// 	center_y = MINIMAP_Y + MINIMAP_SIZE / 2;
// 	k = 1;
// 	while (k <= 15)
// 	{
// 		line_x = center_x + (int)(cos(cub3d->player.angle) * k * 15);
// 		line_y = center_y - (int)(sin(cub3d->player.angle) * k * 15);
// 		if (line_x >= MINIMAP_X && line_x < MINIMAP_X + MINIMAP_SIZE
// 			&& line_y >= MINIMAP_Y && line_y < MINIMAP_Y + MINIMAP_SIZE)
// 			draw_minimap_pixel(cub3d, line_x, line_y, 0x00FF00);
// 		k++;
// 	}
// }

void	draw_player_at_center(t_cub3d *cub3d)
{
	int	center_x;
	int	center_y;
	int	i;
	int	j;

	center_x = MINIMAP_SIZE / 2;
	center_y = MINIMAP_SIZE / 2;
	j = -3;
	while (j <= 3)
	{
		i = -3;
		while (i <= 3)
		{
			draw_minimap_pixel(cub3d, MINIMAP_X + center_x + i, MINIMAP_Y
				+ center_y + j, 0xFF0000);
			i++;
		}
		j++;
	}
}
