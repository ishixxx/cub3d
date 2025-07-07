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


void	player_move(t_cub3d *cub, double dx, double dy, char sign)
{
	// prochaine position potentielle du joueur
	double next_x;
	double next_y;

	// avancer/aller a droite
	if (sign == '+')
	{
		next_x = cub->player.pos.x + dx;
		next_y = cub->player.pos.y + dy;
	}
	// reculer/aller a gauche
	else
	{
		next_x = cub->player.pos.x - dx;
		next_y = cub->player.pos.y - dy;
	}
	// check des collision (mur)
	// on check la case X ou le joueur veut aller
	// si elle contient 0 alors on maj pos_x
	// on separe X et Y pour eviter que le player glisse dans un mur en diagonale
	if (cub->map[(int)(cub->player.pos.y)][(int)(next_x)] == '0')
		cub->player.pos.x = next_x;
	if (cub->map[(int)(next_y)][(int)(cub->player.pos.x)] == '0')
		cub->player.pos.y = next_y;
}

void	player_rotate(t_cub3d *cub, double angle)
{
	double old_dir_x;
	double old_plane_x;

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