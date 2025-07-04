/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:18:26 by vihane            #+#    #+#             */
/*   Updated: 2025/07/04 14:58:00 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_file(char *map_file, t_cub3d *cub3d)
{
	int		fd;
	char	**map_tmp;

	printf("Opening file in init_file: %s\n", map_file);
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		close_game(cub3d, ERR_FILE);
	map_tmp = read_file(fd, cub3d);
	if (!map_tmp)
	{
		close(fd);
		return (close_game(cub3d, ERR_MAP), 1);
	}
	if (close(fd) == -1)
		return (close_game(cub3d, ERR_FILE), 1);
	return (0);
}

void	init_mlx(t_cub3d *cub3d)
{
	cub3d->win_ptr = mlx_new_window(cub3d->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"Cub3D");
	if (!cub3d->win_ptr)
	{
		ft_putstr_fd(ERR_WIN, 2);
		exit(EXIT_FAILURE);
	}
	cub3d->image.data = mlx_new_image(cub3d->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!cub3d->image.data)
	{
		ft_putstr_fd(ERR_IMG, 2);
		exit(EXIT_FAILURE);
	}
	cub3d->image.addr = mlx_get_data_addr(cub3d->image.data, &cub3d->image.bpp,
			&cub3d->image.line_size, &cub3d->image.endian);
	cub3d->image.width = WIN_WIDTH;
	cub3d->image.height = WIN_HEIGHT;
	if (!cub3d->image.addr)
	{
		ft_putstr_fd(ERR_IMG_ADDR, 2);
		exit(EXIT_FAILURE);
	}
}

void	init_data(t_cub3d *cub3d)
{
	cub3d->mlx_ptr = mlx_init();
	if (!cub3d->mlx_ptr)
	{
		ft_putstr_fd(ERR_MLX, 2);
		exit(EXIT_FAILURE);
	}
	cub3d->win_ptr = NULL;
	cub3d->image.data = NULL;
	cub3d->image.addr = NULL;
	cub3d->image.width = 0;
	cub3d->image.height = 0;
	cub3d->image.line_size = 0;
	cub3d->image.endian = 0;
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
	cub3d->texture_north.data = NULL;
	cub3d->texture_south.data = NULL;
	cub3d->texture_west.data = NULL;
	cub3d->texture_east.data = NULL;
}

void	init_player(t_cub3d *cub3d)
{
	cub3d->player.pos.x = 0;
	cub3d->player.pos.y = 0;
	cub3d->player.angle = 0;
	cub3d->player.speed = 0.1;
	cub3d->player.move_up = 0;
	cub3d->player.move_down = 0;
	cub3d->player.move_left = 0;
	cub3d->player.move_right = 0;
	cub3d->player.turn_left = 0;
	cub3d->player.turn_right = 0;
}

void	init_image(t_img *img, char *line, t_cub3d cub3d)
{
	img->data = mlx_xpm_file_to_image(cub3d.mlx_ptr, line, &img->width,
			&img->height);
	if (!img->data)
		close_game(&cub3d, ERR_TEXTURE);
	img->addr = mlx_get_data_addr(img->data, &img->bpp, &img->line_size,
			&img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(cub3d.mlx_ptr, img->data);
		close_game(&cub3d, ERR_TEXTURE_ADDR);
	}
}
