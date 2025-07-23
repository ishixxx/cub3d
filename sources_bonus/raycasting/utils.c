/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:48:16 by vgalmich          #+#    #+#             */
/*   Updated: 2025/07/23 16:55:50 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/* fonction qui retourne la couleur d'un pixel situe aux coordonnees x,y dans
une texture donnee par l'index i */
int	get_color(t_cub3d *cub, int x, int y, int i)
{
	t_img	*tex;
	int		bytes_per_pixel;
	int		offset;
	char	*pixel_address;

	if (i == NORTH)
		tex = &cub->texture_north;
	else if (i == SOUTH)
		tex = &cub->texture_south;
	else if (i == WEST)
		tex = &cub->texture_west;
	else if (i == EAST)
		tex = &cub->texture_east;
	else
		return (0);
	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	bytes_per_pixel = tex->bpp / 8;
	offset = y * tex->line_size + x * bytes_per_pixel;
	pixel_address = tex->addr + offset;
	return (*(unsigned int *)pixel_address);
}

int	get_tex_id(t_cub3d *cub)
{
	if (cub->ray.wall_side == 1 && cub->ray.ray_dir_y < 0)
		return (NORTH);
	if (cub->ray.wall_side == 1 && cub->ray.ray_dir_y > 0)
		return (SOUTH);
	if (cub->ray.wall_side == 0 && cub->ray.ray_dir_x < 0)
		return (WEST);
	return (EAST);
}

int	is_out_of_bounds(t_cub3d *cub)
{
	if (cub->ray.map_y < 0 || cub->ray.map_y >= cub->map_height)
		return (1);
	if (cub->ray.map_x < 0 || cub->ray.map_x >= cub->map_width[cub->ray.map_y])
		return (1);
	return (0);
}

void	advance_ray(t_cub3d *cub)
{
	if (cub->ray.side_dist_x < cub->ray.side_dist_y)
	{
		cub->ray.side_dist_x += cub->ray.delta_dist_x;
		cub->ray.map_x += cub->ray.step_x;
		cub->ray.wall_side = 0;
	}
	else
	{
		cub->ray.side_dist_y += cub->ray.delta_dist_y;
		cub->ray.map_y += cub->ray.step_y;
		cub->ray.wall_side = 1;
	}
}

int	is_wall(t_cub3d *cub)
{
	if (cub->map[cub->ray.map_y][cub->ray.map_x] == '1')
		return (1);
	return (0);
}
