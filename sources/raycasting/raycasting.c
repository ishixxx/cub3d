/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:03:49 by vgalmich          #+#    #+#             */
/*   Updated: 2025/06/25 11:04:42 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* fonction qui calcule la distance qu'un rayon doit parcourir pour
franchir une case de la grille dans chaque direction X ou Y */
void	get_delta_distance(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = INT_MAX;
	else
	// distance qu'un rayon doit parcourir pour passer d'une ligne verticale a l'autre (changer de case en X)
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = INT_MAX;
	else
	// distance qu'un rayon doit parcourir pour passer d'une ligne horizontale a l'autre (changer de case en Y)
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

/* fonction qui :
1. calcule dans quelle direction (step_x, step_y) le rayon doit avancer
2. calcule la distance jusqu'a la premiere grille ver/hor (side_dist)
3. prepare tout pour lancer la boucle DDA
-> indispensable pour lancer le rayon dans la bonne diretion et detecter les
collisions murales
*/
void	set_step_and_side_distance(t_cub3d *cub)
{
	// si le rayon va vers la gauche, on va reculer dans la grille
	if (cub->ray.ray_dir_x < 0)
	{
		cub->ray.step_x = -1
		// calcul de la distance physique pour parcourir jusqu'au premier mur vertical
		cub->ray.side_dist_x = (cub->player.pos.x - cub->ray.map_x) * cub->ray.delta_dist_x;
	}
	else
	{
		cub->ray.step_x = 1;
		cub->ray.side_dist_x = (cub->ray.map_x + 1.0 - cub->player.pos.x) * map->ray.delta_dist_x;
	}
	if (cub->ray.ray_dir_y < 0)
	{
		cub->ray.step_y = -1;
		cub->ray.side_dist_y = (cub->player.pos.y - cub->ray.map_y) * cub->ray.delta_dist_y;
	}
	else
	{
		cub->ray.step_y = 1;
		cub->ray.side_dist_y = (cub->ray.map_y + 1.0 - cub->player.pos.y) * cub->ray.delta_dist_y;
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
Pour chaque colonne X :
1. Initialisation du rayon
2. calcul les distances entre les lignes verticales + horizontales
3. calcul les pas a avancer sur X et Y
4. lancement de la boucle DDA pour trouver le mur
5. calcul de la distance perpendiculaire au mur
3. dessin de la colonne correspondante
*/

