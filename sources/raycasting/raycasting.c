/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:03:49 by vgalmich          #+#    #+#             */
/*   Updated: 2025/06/26 00:46:53 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* fonction qui calcule la distance qu'un rayon doit parcourir pour
franchir une case de la grille dans chaque direction X ou Y */
void	get_delta_distance(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = DBL_MAX;
	else
	// distance qu'un rayon doit parcourir pour passer d'une ligne verticale a l'autre (changer de case en X)
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = INT_MAX;
	else
	// distance qu'un rayon doit parcourir pour passer d'une ligne horizontale a l'autre (changer de case en Y)
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

/* fonction qui determine dans quelle direction traverser la grille
et a quelle distance se trouve la premiere case murale 
-> prepare pour le DDA */
void	setup_dda_steps(t_cub3d *cub)
{
	// si le rayon va vers la gauche, on va reculer dans la grille
	if (cub->ray.ray_dir_x < 0)
	{
		cub->ray.step_x = -1;
		// calcul de la distance physique pour parcourir jusqu'au premier mur vertical
		cub->ray.side_dist_x = (cub->player.pos.x - cub->ray.map_x) * cub->ray.delta_dist_x;
	}
	else
	{
		cub->ray.step_x = 1;
		cub->ray.side_dist_x = (cub->ray.map_x + 1.0 - cub->player.pos.x) * cub->ray.delta_dist_x;
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

/* fonction qui lancer la boucle DDA -> traverse la grille case par case,
jusqu'a rencontrer un mur */
void	digital_differential_analyser(t_cub3d *cub)
{
	int wall;

	wall = 0;
	while (wall == 0)
	{
		// si le mur vertical est + proche
		if (cub->ray.side_dist_x < cub->ray.side_dist_y)
		{
			// traversee verticale
			cub->ray.side_dist_x += cub->ray.delta_dist_x;
			cub->ray.map_x += cub->ray.step_x;
			// on touche un mur vertical
			cub->ray.wall_side = 0;
		}
		else
		{
			cub->ray.side_dist_y += cub->ray.delta_dist_y;
			cub->ray.map_y += cub->ray.step_y;
			// on touche un mur horizontal
			cub->ray.wall_side = 1;
		}
		// check si il y a un mur -> si 1 le point d'impact du rayon est trouve -> stop la boucle
		if (cub->map[cub->ray.map_y][cub->ray.map_x] == '1')
			wall = 1;
	}
}

/* fonction pour initialiser le raycasting */
void	init_raycasting(t_cub3d *cub, int x)
{
	// init des positions de depart
	cub->ray.map_x = (int)cub->player.pos.x;
	cub->ray.map_y = (int)cub->player.pos.y;
	// cam_x -> position horizontale de la camera
	cub->ray.cam_x = 2.0 * (double)cub->win_width - 1.0;
	// calcul de la direction du rayon (+ direction du joueur + camera)
	cub->ray.ray_dir_x = cub->player.dir.x + cub->player.plane.x * cub->ray.cam_x;
	cub->ray.ray_dir_y = cub->player.dir.y + cub->player.plane.y * cub->ray.cam_x;
}

/* fonction qui gere le raycasting */
void	raycasting(t_cub3d *cub)
{
	int	x;

	x = 0;
	while (x < cub->win_width)
	{
		init_raycasting(cub, x);
		get_delta_distance(&cub->ray);
		setup_dda_steps(cub);
		digital_differential_analyse(cub);
		// calcul de la dist perp au mur selon le cote du mur touche
		if (cub->ray.wall_side == 0)
			cub->ray.perp_wall_dist = ((cub->ray.side_dist_x - cub->ray.delta_dist_x));
		else
			cub->ray.perp_wall_dist = ((cub->ray.side_dist_y - cub->ray.delta_dist_y));
		draw_columns(cub, x);
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

