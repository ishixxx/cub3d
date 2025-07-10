/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:44:31 by vgalmich          #+#    #+#             */
/*   Updated: 2025/07/10 16:54:10 by vihane           ###   ########.fr       */
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
		ray->delta_dist_y = DBL_MAX;
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
		cub->ray.side_dist_x = (cub->player.pos.x - cub->ray.map_x)
			* cub->ray.delta_dist_x;
	}
	else
	{
		cub->ray.step_x = 1;
		cub->ray.side_dist_x = (cub->ray.map_x + 1.0 - cub->player.pos.x)
			* cub->ray.delta_dist_x;
	}
	if (cub->ray.ray_dir_y < 0)
	{
		cub->ray.step_y = -1;
		cub->ray.side_dist_y = (cub->player.pos.y - cub->ray.map_y)
			* cub->ray.delta_dist_y;
	}
	else
	{
		cub->ray.step_y = 1;
		cub->ray.side_dist_y = (cub->ray.map_y + 1.0 - cub->player.pos.y)
			* cub->ray.delta_dist_y;
	}
}

/* fonction qui lancer la boucle DDA -> traverse la grille case par case,
jusqu'a rencontrer un mur */
void	digital_differential_analyser(t_cub3d *cub)
{
	int	wall;
	int	max_iterations;
	int	iterations;
	int	current_line_width;

	wall = 0;
	max_iterations = cub->win_width + cub->win_height; // Limite de sécurité
	iterations = 0;
	while (wall == 0 && iterations < max_iterations)
	{
		// Vérification des limites Y
		if (cub->ray.map_y < 0 || cub->ray.map_y >= cub->map_height)
		{
			wall = 1; // Traiter les bords comme des murs
			break ;
		}
		// Obtenir la largeur de la ligne actuelle
		current_line_width = cub->map_width[cub->ray.map_y];
		// Vérification des limites X pour cette ligne
		if (cub->ray.map_x < 0 || cub->ray.map_x >= current_line_width)
		{
			wall = 1; // Traiter les bords comme des murs
			break ;
		}
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
		// Vérifier les limites avant l'accès au tableau
		if (cub->ray.map_y >= 0 && cub->ray.map_y < cub->map_height)
		{
			current_line_width = cub->map_width[cub->ray.map_y];
			if (cub->ray.map_x >= 0 && cub->ray.map_x < current_line_width)
			{
				// check si il y a un mur-> si 1 le point d'impact du rayon est trouve-> stop la boucle
				if (cub->map[cub->ray.map_y][cub->ray.map_x] == '1')
					wall = 1;
			}
			else
			{
				wall = 1; // Hors limites = mur
			}
		}
		else
		{
			wall = 1; // Hors limites = mur
		}
		iterations++;
	}
}

/* fonction pour initialiser le raycasting */
void	init_raycasting(t_cub3d *cub, int x)
{
	// init des positions de depart
	cub->ray.map_x = (int)cub->player.pos.x;
	cub->ray.map_y = (int)cub->player.pos.y;
	// calcul correct de la position horizontale de la caméra
	cub->ray.cam_x = 2.0 * x / (double)cub->win_width - 1.0;
	// calcul de la direction du rayon
	cub->ray.ray_dir_x = cub->player.dir.x + cub->player.plane.x
		* cub->ray.cam_x;
	cub->ray.ray_dir_y = cub->player.dir.y + cub->player.plane.y
		* cub->ray.cam_x;
}

/*
void	init_raycasting(t_cub3d *cub, int x)
{
double	camera_x;

// Calcul de la position du rayon dans l'espace caméra (-1 à +1)
camera_x = 2.0 * x / (double)(cub->win_width) - 1.0;
// Position de départ dans la map
cub->ray.map_x = (int)cub->player.pos.x;
cub->ray.map_y = (int)cub->player.pos.y;
// Direction du rayon
cub->ray.ray_dir_x = cub->player.dir.x + cub->player.plane.x * camera_x;
cub->ray.ray_dir_y = cub->player.dir.y + cub->player.plane.y * camera_x;
// Stocke la valeur pour d'autres étapes
cub->ray.cam_x = camera_x;
}
*/

/* fonction qui gere le raycasting -> simule la vision 3D +
corrige l'effet fish-eye en calcula la distance perpendiculaire
au mur */
void	raycasting(t_cub3d *cub)
{
	int	x;

	x = 0;
	while (x < cub->win_width)
	{
		// printf("raycasting called \n");
		init_raycasting(cub, x);
		get_delta_distance(&cub->ray);
		setup_dda_steps(cub);
		digital_differential_analyser(cub);
		// calcul de la dist perp au mur selon le cote du mur touche
		if (cub->ray.wall_side == 0)
		{
			// Si on touche un mur vertical (côté X)
			cub->ray.perp_wall_dist = (cub->ray.map_x - cub->player.pos.x + (1
						- cub->ray.step_x) / 2) / cub->ray.ray_dir_x;
		}
		else
		{
			// Si on touche un mur horizontal (côté Y)
			cub->ray.perp_wall_dist = (cub->ray.map_y - cub->player.pos.y + (1
						- cub->ray.step_y) / 2) / cub->ray.ray_dir_y;
		}
		draw_wall_column(cub, x);
		x++;
	}
}

/*
void	raycasting(t_cub3d *cub)
{
	int	x;

	x = 0;
	while (x < cub->win_width)
	{
		printf("Raycasting column %d/%d\n", x, cub->win_width - 1);
		// Initialisation des variables du rayon pour la colonne x
		init_raycasting(cub, x);
		printf("init_raycasting done\n");
		// Calcul des distances delta pour le DDA
		get_delta_distance(&cub->ray);
		printf("get_delta_distance done\n");
		// Définition des pas à prendre dans le DDA
		setup_dda_steps(cub);
		printf("setup_dda_steps done\n");
		// Exécution du DDA pour trouver la collision mur
		digital_differential_analyser(cub);
		printf("digital_differential_analyser done\n");
		// Calcul correct de la distance perpendiculaire au mur touché
		if (cub->ray.wall_side == 0)
			cub->ray.perp_wall_dist = (cub->ray.map_x - cub->player.pos.x + (1
						- cub->ray.step_x) / 2) / cub->ray.ray_dir_x;
		else
			cub->ray.perp_wall_dist = (cub->ray.map_y - cub->player.pos.y + (1
						- cub->ray.step_y) / 2) / cub->ray.ray_dir_y;
		// Protection contre division par zéro ou valeurs trop petites
		if (cub->ray.perp_wall_dist < 0.01)
			cub->ray.perp_wall_dist = 0.01;
		printf("perp_wall_dist: %f\n", cub->ray.perp_wall_dist);
		// Dessine la colonne murale correspondante
		draw_wall_column(cub, x);
		printf("draw_wall_column done for column %d\n", x);
		x++;
	}
}
*/