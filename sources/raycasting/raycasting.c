/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:03:49 by vgalmich          #+#    #+#             */
/*   Updated: 2025/06/13 18:49:24 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
Quand on lance un rayon dans une map 2D (vue du dessus), on veut savoir a quel
moment le rayon traverse une ligne veticale ou horizontale de la grille.
Utilisation de l'algorithme DDA, qui avance case par case jusqu'a frapper un
mur -> il faut connaitre a quelle distance le rayon doit parcourir pour traverser
une case en X ou Y (calcul des delta distances)
*/

/* fonction pour avancer le rayon a travers la map et detecter les collisions
avec les murs -> pour le rendu du raycasting */
void    get_delta_distance(t_cub3d *cub)
{
	// si le rayon ne va pas dans la dir X (vertical), la dist pour croiser une ligne verticale est infinie
	if (cub->ray_dir_x == 0)
		cub->delta_dist_x = INT_MAX;
	// sinon on calcule cb d'unite il faut pour passer d'une ligne verticale a la suivante
	else
		cub->delta_dist_x = fabs(1 / cub->ray_dir_x); // si = ray_dir_x = 2 il va vite (1 vitesse 1 case normale)
	// pareil pour l'axe y (horizontal)
	if (cub->ray_dir_y == 0)
		cub->delta_dist_y = INT_MAX;
	else
		cub->delta_dist_y = fabs(1 / cub->ray_dir_y);
}

/* fonction qui :
1. calcule dans quelle direction (step_x, step_y) le rayon doit avancer
2. calcule la distance jusqu'a la premiere grille ver/hor (side_dist)
3. prepare tout pour lancer la boucle DDA
-> indispensable pour lancer le rayon dans la bonne diretion et detecter les
collisions murales
*/
void    set_step_and_side_distance(t_cub3d *cub)
{
	// si le rayon va vers la gauche, on va reculer dans la grille
	if (cub->ray_dir_x < 0)
	{
		cub->step_x = -1
		// calcul de la distance physique pour parcourir jusqu'au premier mur vertical
		cub->side_dist_x = (cub->player->pos->x - cub->map_x) * cub->delta_dist_x;
	}
	// si le rayon va vers la droite, on avance
	else
	{
		cub->step_x = 1;
		cub->side_dist_x = (cub->map_x + 1.0 - cub->player->pos->x) * map->delta_dist_x;
	}
	// pareil pour l'axe y
	if (cub->ray_dir_y < 0)
	{
		cub->step_y = -1;
		cub->side_dist_y = (cub->player->pos->y - cub->map_y) * cub->delta_dist_y;
	}
	else
	{
		cub->step_y = 1;
		cub->side_dist_y = (cub->map_y + 1.0 - cub->player->pos->y) * cub->delta_dist_y;
	}
}

/* fonction pour lancer la boucle DDA -> pour detecter ou le rayon touche un mur */
void    digital_differential_analyser(t_cub3d *cub)
{
	int wall;

	wall = 0;
	while (wall == 0)
	{
		// si le mur vertical est + proche
		if (cub->side_dist_x < cub->side_dist_y)
		{
			// on ajoute delta a side pour la prochaine intersection verticale
			cub->side_dist_x + cub->delta_dist_x;
			cub->map_x += cub->step_x;
			// on touche un mur vertical
			cub->wall_side = 0;
		}
		else
		{
			cub->side_dist_y += cub->delta_dist_y;
			cub->map_y += cub->step_y;
			// on touche un mur horizontal
			cub->wall_side = 1;
		}
		// check si il y a un mur -> si 1 le point d'impact du rayon est trouve -> stop la boucle
		if (cub->map[cub->map_y][cub->map_x] == '1')
			wall = 1;
	}
}

/* fonction pour initialiser le raycasting */
void	init_raycasting(t_cub3d *cub, int x)
{
	// init des positions de depart
	cub->map_x = cub->player->pos->x;
	cub->map_y = cub->player->pos->y;
	// cam_x -> position horizontale de la camera
	cub->cam_x = 2 * (double)cub->map_width - 1;
	// calcul de la direction du rayon (+ direction du joueur + camera)
	cub->ray_dir_x = cub->player->dir->x + cub->player->plane->x * cub->cam_x;
	cub->ray_dir_y = cub->player->dir->y + cub->player->plane->y * cub->cam_x;
}

/* fonction qui gere le raycasting */
void	raycasting(t_cub3d *cub)
{
	int	x;

	x = 0;
	while (x < cub->map_width)
	{
		init_raycasting(cub, x);
		get_delta_distance(cub);
		set_step_and_side_distance(cub);
		digital_differential_analyse(cub);
		// calcul de la dist perp au mur selon le cote du mur touche
		if (cub->wall_side = 0)
			cub->perp_wall_dist = ((cub->side_dist_x - cub->delta_dist_x));
		else
			cub->perp_wall_dist = ((cub->side_dist_y - cub->delta_dist_y));
		draw_columns(cub, x); // coder fonction pour dessiner les colonnes
		x++;
	}
}

/*
ETAPES :
raycasting

Boucle sur chaque colonne x de la fenêtre.

Pour chaque colonne :

Initialise le rayon (init_raycasting).

Calcule les distances entre les lignes verticales/horizontales (get_delta_dist).

Calcule le pas à avancer en X et Y (set_step_and_side_distance).

Lance la boucle DDA pour trouver le mur (digital_differential_analyser).

Calcule la distance perpendiculaire au mur (perp_wall_dist) selon le côté du mur touché.

Dessine la colonne correspondante (coder une fonction draw_column).
*/

