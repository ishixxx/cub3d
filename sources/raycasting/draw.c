/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:04:20 by vgalmich          #+#    #+#             */
/*   Updated: 2025/07/03 14:27:40 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// fonction pour dessiner un pixel de couleur dans une image memoire
void	draw_pixel(t_img *img, t_point p, int color)
{
	char	*pixel;
	int		x;
	int		y;

	x = (int)p.x;
	y = (int)p.y;
	 // si les coordonnees depassent la fenetre -> on ne dessine pas
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return;
	// calcul de l'adresse memoire precise ou est stocke le pixel
	pixel = img->addr + (y * img->line_size + x * (img->bpp / 8));
	// on fait un cast pour pouvoir modifier un pixel ->
	// on ecrit 4 octets en une seule operation
	*(unsigned int *)pixel = color;
}


/* fonction qui calcule la hauteur du mur a dessiner en fonction de la
distance au mur (perp_wall_dist) et trouve les coordonnees verticales de
début et de fin pour cette colones */
void	calculate_wall_slice(t_cub3d *cub, int *line_height, int *start, int *end)
{
	// calcul de la hauteur du mur projete a l'ecran
	*line_height = (int)cub->win_height / cub->ray.perp_wall_dist;
	// calcul du pointde depart vertical (debut du mur)
	*start = -(*line_height) / 2 * cub->win_height / 2;
	// si depassement, on coupe
	if (*start < 0)
		*start = 0;
	// calcul du point de fin vertical (fin du mur)
	*end = *line_height / 2 + cub->win_height / 2;
	if (*end >= cub->win_height)
		*end = cub->win_height - 1;
}

/* fonction qui prepare tous les parametres pour mapper correctement
une texture murale sur une colonne verticale de l'ecran, en fonction de
la ou le rayon a frappe le mur */
void	calculate_tex_mapping(t_cub3d *cub, int start, int line_height)
{
	// calcul de la position ou le rayon touche le mur
	if (cub->ray.wall_side == 0)
		cub->ray.wall_x = cub->player.pos.y + cub->ray.perp_wall_dist * cub->ray.ray_dir_y;
	else
		cub->ray.wall_x = cub->player.pos.x + cub->ray.perp_wall_dist * cub->ray.ray_dir_x;
	// on garde la partie decimale pour localiser l'impact sur le mur
	cub->ray.wall_x -= floor(cub->ray.wall_x); // fonction mathematique qui retourne la + grande valeur entiere inferieure ou egale a un nb donne
	// calcul la coordonnee texture_x (colonne de texture a prelever)
	cub->ray.tex_x = cub->ray.wall_x * 128; // 128 pixels de large pour la texture
	// on ajuste texture_x si le mur est vu de l'autre cote
	if (cub->ray.wall_side == 0 && cub->ray.ray_dir_x > 0)
		cub->ray.tex_x = 128 - cub->ray.tex_x - 1;
	if (cub->ray.wall_side == 1 && cub->ray.ray_dir_y < 0)
		cub->ray.tex_x = 128 - cub->ray.tex_x - 1;
	// calcul du pas de progression vertical dans la texture
	cub->ray.step = 1.0 * 128 / line_height;
	// calcul de la pos depart dans la tex pour la 1ere ligne affichee
	cub->ray.tex_pos = (start - cub->win_height / 2 + line_height / 2) * cub->ray.step;
}

/* fonction pour dessiner un pixel vertical de mur a l'ecran a la colonne x
avec la bonne couleur prelevee depuis la texture */
void	draw_wall_pixel(t_cub3d *cub, t_point pos, int texture)
{
	int		color;
	t_point	p;

	p.x = (int)pos.x;
	p.y = (int)pos.y;
	color = get_color(cub, cub->ray.tex_x, cub->ray.tex_y, texture);
	draw_pixel(&cub->image, p, color);
}

/* fonction qui trace une ligne verticale sur l'ecran representant un mur*/
void 	draw_wall_column(t_cub3d *cub, int x)
{
	int		line_height;
	int		start;
	int		end;
	int		y;
	t_point	pixel_pos;
	int		tex_id;
	// calculer la hauteur et les limites de la colonne
	calculate_wall_slice(cub, &line_height, &start, &end);
	// calculer les coordonnees de texture
	calculate_tex_mapping(cub, start, line_height);
	// boucle de dessin pixel par pixel de la colonne verticale
	y = start;
	while (y < end)
	{
		// calculer la coordonee Y dans la texture
		cub->ray.tex_y = (int)cub->ray.tex_pos & (128 - 1);
		// avancer dans la texture
		cub->ray.tex_pos += cub->ray.step;
		// pos ecran a dessiner
		pixel_pos.x = x;
		pixel_pos.y = y;
		// determiner la bonne tex selon le cote du mur touche
		if (cub->ray.wall_side == 1 && cub->ray.ray_dir_y < 0)
			tex_id = SOUTH;
		else if (cub->ray.wall_side == 1 && cub->ray.ray_dir_y > 0)
			tex_id = NORTH;
		else if (cub->ray.wall_side == 0 && cub->ray.ray_dir_x < 0)
			tex_id = WEST;
		else if (cub->ray.wall_side == 0 && cub->ray.ray_dir_x > 0)
			tex_id = EAST;
		draw_wall_pixel(cub, pixel_pos, tex_id);
		y++;
	}
}