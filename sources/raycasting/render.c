/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:04:24 by vgalmich          #+#    #+#             */
/*   Updated: 2025/07/10 16:53:34 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// fonctin qui cree une couleur
int	create_trgb(int t, t_color color)
{
	return (t << 24 | color.r << 16 | color.g << 8 | color.b);
}

// fonction pour remplir l'image de fond de la fenetre (avec les couleurs ciel + sol)
void	render_background(t_cub3d *cub)
{
	int		x;
	int		y;
	t_point	p;

	x = 0;
	while (x < cub->win_width)
	{
		y = 0;
		while (y < cub->win_height)
		{
			p.x = (double)x;
			p.y = (double)y;
			if (y < cub->win_height / 2) // si on est a la moitie haute de l'ecran
				draw_pixel(cub, p, create_trgb(0, cub->ceiling)); // coder ces 2 fonctions
			else
				draw_pixel(cub, p, create_trgb(0, cub->floor));
			y++;
		}
		x++;
	}	
}

int	render_3D_scene(void *param)
{
	t_cub3d *cub;
	cub = (t_cub3d *)param;
	render_background(cub); // fonction OK
	raycasting(cub); // pb dans raycasting
	put_img_to_window(cub);
	return (0);
}

void put_img_to_window(t_cub3d *cub3d)
{
	if (mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr, cub3d->image.data, 0, 0) == -1)
		close_game(cub3d, "Failed to put image to window.\n");
}