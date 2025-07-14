/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:18:26 by vihane            #+#    #+#             */
/*   Updated: 2025/07/14 13:42:14 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_mlx(t_cub3d *cub3d)
{
	cub3d->win_ptr = mlx_new_window(cub3d->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"Cub3D");
	if (!cub3d->win_ptr)
		close_game(cub3d, ERR_WIN);
	cub3d->image.data = mlx_new_image(cub3d->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!cub3d->image.data)
		close_game(cub3d, ERR_IMG);
	cub3d->image.addr = mlx_get_data_addr(cub3d->image.data, &cub3d->image.bpp,
			&cub3d->image.line_size, &cub3d->image.endian);
	cub3d->image.width = WIN_WIDTH;
	cub3d->image.height = WIN_HEIGHT;
	cub3d->win_width = WIN_WIDTH;
	cub3d->win_height = WIN_HEIGHT;
	if (!cub3d->image.addr)
		close_game(cub3d, ERR_IMG_ADDR);
	printf("MLX initialized successfully\n");
}

void	init_data(t_cub3d *cub3d)
{
	cub3d->mlx_ptr = mlx_init();
	if (!cub3d->mlx_ptr)
		simple_exit(ERR_MLX);
	cub3d->win_ptr = NULL;
	cub3d->image.data = NULL;
	cub3d->image.addr = NULL;
	cub3d->map = NULL;
	cub3d->map_width = 0;
	cub3d->map_height = 0;
	cub3d->floor.r = -1; // -1 car non definie
	cub3d->floor.g = -1;
	cub3d->floor.b = -1;
	cub3d->ceiling.r = -1;
	cub3d->ceiling.g = -1;
	cub3d->ceiling.b = -1;
	init_texture(cub3d);
	init_player(cub3d);
}

void	init_texture(t_cub3d *cub3d)
{
	cub3d->map_view = 0;
	cub3d->textture_view = 0;
	cub3d->texture_north.data = NULL;
	cub3d->texture_south.data = NULL;
	cub3d->texture_west.data = NULL;
	cub3d->texture_east.data = NULL;
}

void	init_player(t_cub3d *cub3d)
{
	cub3d->player.pos.x = -1; // -1 car non definie
	cub3d->player.pos.y = -1; // -1 car non definie
	cub3d->player.dir.x = 1.0;
	cub3d->player.dir.y = 0.0;
	cub3d->player.plane.x = 0.0;
	cub3d->player.plane.y = 0.66;
	cub3d->player.angle = 0;
	cub3d->player.speed = 0.1;
	cub3d->player.move_up = 0;
	cub3d->player.move_down = 0;
	cub3d->player.move_left = 0;
	cub3d->player.move_right = 0;
	cub3d->player.turn_left = 0;
	cub3d->player.turn_right = 0;
}
