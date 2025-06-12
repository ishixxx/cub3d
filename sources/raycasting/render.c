/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:04:24 by vgalmich          #+#    #+#             */
/*   Updated: 2025/06/12 19:02:33 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
- fonction pour le rendu du background avec display width et display height
- fonction render avec render background + raycasting + mlx_put_image_to_window
*/

// fonction pour remplir l'image de fond de la fenetre (avec les couleurs ciel + sol)
void    render_background(t_img *map)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x < map->width)
    {
        while (y < map->height)
        {
            if (y < map->win_height / 2) // si on est a la moitie haute de l'ecran
                draw_colored_pixel(map, x, y, create_trgb()) // coder ces 2 fonctions
            else
                draw_colored_pixel(map, x, y)
        }
    }

    
}