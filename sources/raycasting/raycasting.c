/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:44:31 by vgalmich          #+#    #+#             */
/*   Updated: 2025/07/15 17:27:43 by vihane           ###   ########.fr       */
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
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = DBL_MAX;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

/* fonction qui determine dans quelle direction traverser la grille
et a quelle distance se trouve la premiere case murale
-> prepare pour le DDA */
void	setup_dda_steps(t_cub3d *cub)
{
	if (cub->ray.ray_dir_x < 0)
	{
		cub->ray.step_x = -1;
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

	wall = 0;
	max_iterations = cub->win_width + cub->win_height;
	iterations = 0;
	cub->ray.wall_side = -1;
	while (wall == 0 && iterations < max_iterations)
	{
		if (is_out_of_bounds(cub) || is_wall(cub))
			wall = 1;
		else
		{
			advance_ray(cub);
		}
		iterations++;
	}
	if (cub->ray.wall_side == -1)
		cub->ray.wall_side = 0;
}

/* fonction pour initialiser le raycasting */
void	init_raycasting(t_cub3d *cub, int x)
{
	cub->ray.map_x = (int)cub->player.pos.x;
	cub->ray.map_y = (int)cub->player.pos.y;
	cub->ray.cam_x = 2.0 * x / (double)cub->win_width - 1.0;
	cub->ray.ray_dir_x = cub->player.dir.x + cub->player.plane.x
		* cub->ray.cam_x;
	cub->ray.ray_dir_y = cub->player.dir.y + cub->player.plane.y
		* cub->ray.cam_x;
}

/* fonction qui gere le raycasting -> simule la vision 3D +
corrige l'effet fish-eye en calcula la distance perpendiculaire
au mur */
void	raycasting(t_cub3d *cub)
{
	int	x;

	x = 0;
	while (x < cub->win_width)
	{
		init_raycasting(cub, x);
		get_delta_distance(&cub->ray);
		setup_dda_steps(cub);
		digital_differential_analyser(cub);
		if (cub->ray.wall_side == 0)
		{
			cub->ray.perp_wall_dist = (cub->ray.map_x - cub->player.pos.x + (1
						- cub->ray.step_x) / 2) / cub->ray.ray_dir_x;
		}
		else
		{
			cub->ray.perp_wall_dist = (cub->ray.map_y - cub->player.pos.y + (1
						- cub->ray.step_y) / 2) / cub->ray.ray_dir_y;
		}
		draw_wall_column(cub, x);
		x++;
	}
}
