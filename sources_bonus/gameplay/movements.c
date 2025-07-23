/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:43:38 by vgalmich          #+#    #+#             */
/*   Updated: 2025/07/23 13:43:38 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	is_line_free(t_cub3d *cub, int j, int min_x, int max_x)
{
	int	i;

	if (j < 0 || j >= cub->map_height || !cub->map[j])
		return (0);
	i = min_x;
	while (i <= max_x)
	{
		if (i < 0 || i >= (int)ft_strlen(cub->map[j]))
			return (0);
		if (cub->map[j][i] == '1')
			return (0);
		i++;
	}
	return (1);
}

int	is_position_free(t_cub3d *cub, double x, double y)
{
	int	min_x;
	int	max_x;
	int	min_y;
	int	max_y;
	int	j;

	min_x = (int)(x - COLLISION_RADIUS);
	max_x = (int)(x + COLLISION_RADIUS);
	min_y = (int)(y - COLLISION_RADIUS);
	max_y = (int)(y + COLLISION_RADIUS);
	j = min_y;
	while (j <= max_y)
	{
		if (!is_line_free(cub, j, min_x, max_x))
			return (0);
		j++;
	}
	return (1);
}

void	player_move(t_cub3d *cub, double dx, double dy, char sign)
{
	double	next_x;
	double	next_y;

	if (sign == '+')
	{
		next_x = cub->player.pos.x + dx;
		next_y = cub->player.pos.y + dy;
	}
	else
	{
		next_x = cub->player.pos.x - dx;
		next_y = cub->player.pos.y - dy;
	}
	if (is_position_free(cub, next_x, cub->player.pos.y))
		cub->player.pos.x = next_x;
	if (is_position_free(cub, cub->player.pos.x, next_y))
		cub->player.pos.y = next_y;
}

void	player_rotate(t_cub3d *cub, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player.dir.x;
	old_plane_x = cub->player.plane.x;
	cub->player.dir.x = cub->player.dir.x * cos(angle) - cub->player.dir.y
		* sin(angle);
	cub->player.dir.y = old_dir_x * sin(angle) + cub->player.dir.y
		* cos(angle);
	cub->player.plane.x = cub->player.plane.x * cos(angle) - cub->player.plane.y
		* sin(angle);
	cub->player.plane.y = old_plane_x * sin(angle) + cub->player.plane.y
		* cos(angle);
}
