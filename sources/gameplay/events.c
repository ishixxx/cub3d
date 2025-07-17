/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:29:20 by vihane            #+#    #+#             */
/*   Updated: 2025/07/17 20:24:36 by vihane           ###   ########.fr       */
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
	if (keycode == ESC)
		close_window(cub3d);
	else if (keycode == W_KEY || keycode == UP_ARROW)
		player_move(cub3d, cub3d->player.dir.x * move_speed, cub3d->player.dir.y
			* move_speed, '+');
	else if (keycode == S_KEY || keycode == DOWN_ARROW)
		player_move(cub3d, cub3d->player.dir.x * move_speed, cub3d->player.dir.y
			* move_speed, '-');
	else if (keycode == D_KEY)
		player_move(cub3d, -cub3d->player.dir.y * move_speed,
			cub3d->player.dir.x * move_speed, '+');
	else if (keycode == A_KEY)
		player_move(cub3d, cub3d->player.dir.y * move_speed,
			-cub3d->player.dir.x * move_speed, '+');
	else if (keycode == RIGHT_ARROW)
		player_rotate(cub3d, rotation_speed);
	else if (keycode == LEFT_ARROW)
		player_rotate(cub3d, -rotation_speed);
	return (0);
}

int	close_window(t_cub3d *cub3d)
{
	free_cub(cub3d);
	free_mlx(cub3d);
	exit(EXIT_SUCCESS);
	return (0);
}
