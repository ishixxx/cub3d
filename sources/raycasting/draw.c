/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:04:20 by vgalmich          #+#    #+#             */
/*   Updated: 2025/06/12 20:12:43 by vgalmich         ###   ########.fr       */
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

// fonction pour preparer les colonnes
void    define_columns(t_img *img, int *line_height, int *start, int *end)
