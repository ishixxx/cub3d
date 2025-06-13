/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:04:20 by vgalmich          #+#    #+#             */
/*   Updated: 2025/06/13 18:49:32 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// coder la lecture des couleurs

// fonction pour dessiner un pixel colore
void    draw_colored_pixel(t_img *img, int x, int y, int color)
{
    char    *pixel;

     // si les coordonnees depassent la fenetre -> on ne dessine pas
    if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return;
    // calcul de l'adresse memoire precise ou est stocke le pixel
    pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
    // on fait un cast pour pouvoir modifier un pixel ->
    // on ecrit 4 octets en une seule operation
    (unsigned int *)pixel = color;
}


// fonction qui calcule la hauteur et les positions verticales d'un mur a afficher
/*
ETAPES ->
1. lancer un rayon pour savoir ou il frappe un mur
2. calculer la distance du mur par rapport au joueur
3. en fonction de la distance, calculer la hauteur du mur a afficher (line_height)+ position de depart et fin de la ligne verticale
*/
void    define_columns(t_cub3d *cub, int *line_height, int *start, int *end)
{
    // calcul de la hauteur de la ligne a tracer
    *line_height = cub->win_height / cub->perp_wall_dist;
    // centrer le mur verticalement a l'ecran
    // le sommet du mur se place a demi hauteur au dessus du centre de l'ecran
    *start = *line_height / 2 * cub->win_height / 2;
    // si depassement, on coupe
    if (*start < 0)
        *start = 0;
    // calcul du bas du mur, a demi hauteur en dessous du centre de l'ecran
    *end = *line_height / 2 + cub->win_height / 2;
    if (*end >= cub->win_height)
        *end = cub->win_height - 1;
}

void    define_textures