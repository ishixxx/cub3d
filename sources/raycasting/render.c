/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:04:24 by vgalmich          #+#    #+#             */
/*   Updated: 2025/06/29 19:55:14 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// fonctin qui cree une couleur
int create_trgb(int t, t_color color)
{
	return (t << 24 | color.r << 16 | color.g << 8 | color.b);
}

// fonction pour remplir l'image de fond de la fenetre (avec les couleurs ciel + sol)
void	render_background(t_cub3d *cub)
{
	int x;
	int y;
	t_point p;

	x = 0;
	while (x < cub->win_width)
	{
		y = 0;
		while (y < cub->win_height)
		{
			p.x = (double)x;
			p.y = (double)y;
			if (y < cub->win_height / 2) // si on est a la moitie haute de l'ecran
				draw_pixel(&cub->image, p, create_trgb(0, cub->ceiling.r, cub->ceiling.g, cub->ceiling.b)); // coder ces 2 fonctions
			else
				draw_pixel(&cub->image, p, create_trgb(0, cub->floor.r, cub->floor.g, cub->floor.b));
			y++;
		}
		++x;
	}	
}

void	render_3D_scene(t_cub3d *cub)
{
	render_background(cub);
	raycasting(cub);
	mlx_put_img_to_window(cub->mlx, cub->mlx_win, cub->img[4].mlx_img, 0, 0);
	return (0);
}