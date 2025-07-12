/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/07/02 20:04:21 by vgalmich          #+#    #+#             */
/*   Updated: 2025/07/02 20:04:21 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int is_position_free(t_cub3d *cub, double x, double y)
{
	int min_x = (int)(x - COLLISION_RADIUS);
	int max_x = (int)(x + COLLISION_RADIUS);
	int min_y = (int)(y - COLLISION_RADIUS);
	int max_y = (int)(y + COLLISION_RADIUS);

	for (int j = min_y; j <= max_y; j++)
	{
		// Vérifie que j est dans les bornes verticales
		if (j < 0 || j >= cub->map_height)
			return 0;

		for (int i = min_x; i <= max_x; i++)
		{
			// Vérifie que i est dans les bornes horizontales de la ligne j
			if (i < 0 || i >= (int)ft_strlen(cub->map[j]))
				return 0;

			if (cub->map[j][i] == '1')
				return 0;
		}
	}
	return 1;
}

void	player_move(t_cub3d *cub, double dx, double dy, char sign)
{
	double next_x;
	double next_y;

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
	// Collision avec marge
	if (is_position_free(cub, next_x, cub->player.pos.y))
		cub->player.pos.x = next_x;
	if (is_position_free(cub, cub->player.pos.x, next_y))
		cub->player.pos.y = next_y;
}

void	player_rotate(t_cub3d *cub, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	// rotation du vecteur direction (ou le joueur regarde)
	old_dir_x = cub->player.dir.x;
	// rotation du plan de la camera (champ de vision)
	old_plane_x = cub->player.plane.x;
	cub->player.dir.x = cub->player.dir.x * cos(angle) - cub->player.dir.y
		* sin(angle);
	cub->player.dir.y = old_dir_x * sin(angle) + cub->player.dir.y
		* cos(angle);
	// garder le champ de vision aligne a la nouvelle direction
	cub->player.plane.x = cub->player.plane.x * cos(angle) - cub->player.plane.y
		* sin(angle);
	cub->player.plane.y = old_plane_x * sin(angle) + cub->player.plane.y
		* cos(angle);
}
