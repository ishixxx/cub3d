/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:29:20 by vihane            #+#    #+#             */
/*   Updated: 2025/07/10 19:22:01 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// utiliser fonction move et rotate

int	keypress(int keycode, t_cub3d *cub3d)
{
	double	move_speed;
	double	rotation_speed;

	move_speed = 0.1;
	rotation_speed = 0.05;
	if (keycode == ESC) // fermer le jeu
		close_window(cub3d);
	else if (keycode == W_KEY || keycode == UP_ARROW) // avancer
		player_move(cub3d, cub3d->player.dir.x * move_speed, cub3d->player.dir.y
			* move_speed, '+');
	else if (keycode == S_KEY || keycode == DOWN_ARROW) // reculer
		player_move(cub3d, cub3d->player.dir.x * move_speed, cub3d->player.dir.y
			* move_speed, '-');
	else if (keycode == D_KEY) // mouvement latéral droite
		player_move(cub3d, cub3d->player.dir.y * move_speed, cub3d->player.dir.x
			* move_speed, '+');
	else if (keycode == A_KEY) // mouvement latéral gauche
		player_move(cub3d, cub3d->player.dir.y * move_speed, cub3d->player.dir.x
			* move_speed, '-');
	else if (keycode == RIGHT_ARROW) // tourner à droite
		player_rotate(cub3d, rotation_speed);
	else if (keycode == LEFT_ARROW) // tourner à gauche
		player_rotate(cub3d, -rotation_speed);
	return (0);
}

int	close_window(t_cub3d *cub3d)
{
	mlx_destroy_display(cub3d->mlx_ptr);
	mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
	free_map(cub3d);
	exit(0);
}