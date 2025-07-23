/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:27:30 by vihane            #+#    #+#             */
/*   Updated: 2025/07/23 13:49:26 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	mouse_move(int x, int y, t_cub3d *cub3d)
{
	static int	last_x = -1;
	int			delta_x;
	double		rotation_speed;

	(void)y;
	rotation_speed = 0.002;
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	delta_x = x - last_x;
	last_x = x;
	if (delta_x != 0)
		player_rotate(cub3d, delta_x * rotation_speed);
	return (0);
}
