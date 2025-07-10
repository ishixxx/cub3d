/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/07/02 22:41:31 by vgalmich          #+#    #+#             */
/*   Updated: 2025/07/02 22:41:31 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_game(t_cub3d *cub)
{
	if (!cub->image.addr)
		close_game(cub, ERR_IMG_INIT);
	printf("Game is starting\n");
	mlx_hook(cub->win_ptr, 2, 1L << 0, keypress, cub);
	mlx_hook(cub->win_ptr, 17, 1L << 0, close_game, cub);
	mlx_loop_hook(cub->mlx_ptr, render_scene, cub);
	mlx_loop(cub->mlx_ptr);
	return (0);
}
