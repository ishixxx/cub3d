/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:04:24 by vgalmich          #+#    #+#             */
/*   Updated: 2025/06/21 13:34:11 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
- fonction pour le rendu du background avec display width et display height
- fonction render avec render background + raycasting + mlx_put_image_to_window
*/

// fonctin qui cree une couleur
int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 || r << 16 | g << 8 | b);
}

// fonction pour remplir l'image de fond de la fenetre (avec les couleurs ciel + sol)
void	render_background(t_cub3d *cub)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < cub->win_width)
	{
		while (y < cub->win_height)
		{
			if (y < cub->win_height / 2) // si on est a la moitie haute de l'ecran
				draw_colored_pixel(cub, x, y, create_trgb(0, cub->sky_rgb[0], cub->sky_rgb[1], cub->sky_rgb[2])); // coder ces 2 fonctions
			else
				draw_colored_pixel(cub, x, y, create_trgb(0, cub->floor_rgb[0], cub->floor_rgb[1], cub->florr_rgb[2]));
			y++;
		}
		++x
	}	
}

void	render_3D_scene(t_cub3d *cub)
{
	render_background(cub);
	raycasting(cub);
	mlx_put_img_to_window(cub->mlx, cub->mlx_win, cub->img[4].mlx_img, 0, 0);
	return (0);
}