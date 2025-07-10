/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:48:16 by vgalmich          #+#    #+#             */
/*   Updated: 2025/07/10 18:27:14 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
