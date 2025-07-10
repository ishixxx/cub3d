/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:04:20 by vgalmich          #+#    #+#             */
/*   Updated: 2025/07/10 18:23:11 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// fonction pour dessiner un pixel de couleur dans une image memoire
void	draw_pixel(t_cub3d *cub, t_point p, int color)
{
	char	*pixel;
	int		x;
	int		y;

	x = (int)p.x;
	y = (int)p.y;
	// si les coordonnees depassent la fenetre -> on ne dessine pas
	if (x < 0 || x >= cub->image.width || y < 0 || y >= cub->image.height)
		return ;
	// calcul de l'adresse memoire precise ou est stocke le pixel
	pixel = cub->image.addr + (y * cub->image.line_size + x * (cub->image.bpp
				/ 8));
	// on fait un cast pour pouvoir modifier un pixel ->
	// on ecrit 4 octets en une seule operation
	*(unsigned int *)pixel = color;
}

/* fonction qui calcule la hauteur du mur a dessiner en fonction de la
distance au mur (perp_wall_dist) et trouve les coordonnees verticales de
début et de fin pour cette colones */
void	calculate_wall_slice(t_cub3d *cub, int *line_height, int *start,
		int *end)
{
	// Protection contre les distances trop petites
	if (cub->ray.perp_wall_dist < 0.1)
		cub->ray.perp_wall_dist = 0.1;
	// Hauteur projetée du mur - SIMPLIFIÉ
	*line_height = (int)(cub->win_height / cub->ray.perp_wall_dist);
	// Centre l'affichage du mur verticalement - SIMPLIFIÉ
	*start = (cub->win_height - *line_height) / 2;
	*end = *start + *line_height - 1;
	// Clamp les bornes pour éviter les débordements
	if (*start < 0)
		*start = 0;
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
		cub->ray.wall_x = cub->player.pos.y + cub->ray.perp_wall_dist
			* cub->ray.ray_dir_y;
	else
		cub->ray.wall_x = cub->player.pos.x + cub->ray.perp_wall_dist
			* cub->ray.ray_dir_x;
	// on garde la partie decimale pour localiser l'impact sur le mur
	cub->ray.wall_x -= floor(cub->ray.wall_x);
	// calcul la coordonnee texture_x (colonne de texture a prelever)
	cub->ray.tex_x = (int)(cub->ray.wall_x * TEXTURE_WIDTH);
	// on ajuste texture_x si le mur est vu de l'autre cote
	if (cub->ray.wall_side == 0 && cub->ray.ray_dir_x > 0)
		cub->ray.tex_x = TEXTURE_WIDTH - cub->ray.tex_x - 1;
	if (cub->ray.wall_side == 1 && cub->ray.ray_dir_y < 0)
		cub->ray.tex_x = TEXTURE_WIDTH - cub->ray.tex_x - 1;
	// calcul du pas de progression vertical dans la texture
	cub->ray.step = 1.0 * TEXTURE_HEIGHT / line_height;
	// calcul de la pos depart dans la tex pour la 1ere ligne affichee
	cub->ray.tex_pos = (start - cub->win_height / 2 + line_height / 2)
		* cub->ray.step;
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
	draw_pixel(cub, p, color);
}

/* fonction qui trace une ligne verticale sur l'ecran representant un mur*/
void	draw_wall_column(t_cub3d *cub, int x)
{
	int line_height;
	int start;
	int end;
	int y;
	t_point pixel_pos;
	int tex_id;
	// calculer la hauteur et les limites de la colonne
	// printf("perp_wall_dist: %.3f\n", cub->ray.perp_wall_dist);
	calculate_wall_slice(cub, &line_height, &start, &end);
	// printf("line_height: %d, start: %d, end: %d\n", line_height, start, end);
	// calculer les coordonnees de texture
	calculate_tex_mapping(cub, start, line_height);
	// boucle de dessin pixel par pixel de la colonne verticale
	y = start;
	while (y <= end)
	{
		// calculer la coordonee Y dans la texture
		// cub->ray.tex_y = (int)cub->ray.tex_pos & (64 - 1);
		cub->ray.tex_y = (int)cub->ray.tex_pos % TEXTURE_HEIGHT;
		if (cub->ray.tex_y < 0)
			cub->ray.tex_y += TEXTURE_HEIGHT;
		// avancer dans la texture
		cub->ray.tex_pos += cub->ray.step;
		// pos ecran a dessiner
		pixel_pos.x = x;
		pixel_pos.y = y;
		// determiner la bonne tex selon le cote du mur touche
		if (cub->ray.wall_side == 1 && cub->ray.ray_dir_y < 0)
			tex_id = NORTH;
		else if (cub->ray.wall_side == 1 && cub->ray.ray_dir_y > 0)
			tex_id = SOUTH;
		else if (cub->ray.wall_side == 0 && cub->ray.ray_dir_x < 0)
			tex_id = WEST;
		else if (cub->ray.wall_side == 0 && cub->ray.ray_dir_x > 0)
			tex_id = EAST;
		draw_wall_pixel(cub, pixel_pos, tex_id);
		y++;
	}
}
