/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:04:20 by vgalmich          #+#    #+#             */
/*   Updated: 2025/06/19 16:39:58 by vgalmich         ###   ########.fr       */
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

/* fonction pour determiner la position exacte de la colonne de texture a afficher
sur un mur, en fonction de l'impact du rayon sur le mur et la taille de la ligne
verticale a dessiner */
void    setup_wall_texture(t_cub3d *cub, int start, int line_height)
{
    // 1. calcul de la position de l'impact sur le mur
    if (cub->wall_side == 0)
        cub->wall_x = cub->player->pos->y + cub->perp_wall_dist * cub->ray_dir_y;
    else
         cub->wall_x = cub->player->pos->x + cub->perp_wall_dist * cub->ray_dir_x;
    // 2. on garde la partie decimale pour localiser l'impact sur le mur
    cub->wall_x -= floor(cub->wall_x); // fonction mathematique qui retourne la + grande valeur entiere inferieure ou egale a un nb donne
    // 3. calcul la coordonnee texture_x (colonne de texture a prelever)
    cub->texture_x = cub->wall_x * 128; // 128 pixels de large pour la texture
    // 4. on ajuste texture_x si le mur est vu de l'autre cote
    if (cub->wall_side == 0 && cub->ray_dir_x > 0)
        cub->texture_x = 128 - cub->texture_x - 1;
    if (cub->wall_side == 1 && cub->ray_dir_y < 0)
        cub->texture_x = 128 - cub->texture_x - 1;
    // 5. calcul du pas de progression vertical dans la texture
    cub->step = 1.0 * 128 / line_height;
    // 6. position initale dans la texture pour la premiere ligne affichee
    cub->texture_pos = (start - cub->win_height / 2 + line_height / 2) * cub->step;
}

/* fonction pour dessiner un pixel vertical de mur a l'ecran a la colonne x
avec la bonne couleur prelevee depuis la texture */
void    draw_wall_pixel(t_cub3d *cub, int x, int texture)
{
    int color;
    color = get_color(cub, cub->texture_x, cub->teture_y, texture);
    draw_colored_pixel(cub, c, cub->start, color);
}

/* fonction qui trace une ligne verticale sur l'ecran representant un mur*/
void    draw_wall_column(t_cub3d *cub, int x)
{
    // 1. definir la hauteur et les limites de la colonne
    int line_height;
    define_columns(cub, &line_height, &cub->start, &cub->end);
    // 2. configurer les coordonnees de texture
    setup_wall_texture(cub, cub->start, line_height);
    // 3. boucle de dessin de la colonne
    while (cub->start < cub->end)
    // on dessine pixel par pixel
    {
        cub->texture_y = (int)cub->texture_pos & (128 - 1);
        cub->texture_pos += cub->step;
        // determiner la direction du mur
        if (cub->wall_side == 1 && cub->ray_dir_y < 0)
            draw_wall_pixel(cub, x, SOUTH);
        else if (cub->wall_side == 1 && cub->ray_dir_y > 0)
            draw_wall_pixel(cub, x, NORTH);
        else if (cub_>wall_side == 0 && cub->ray_dir_x < 0)
            draw_wall_pixel(cub, x, WEST);
        else if (cub->wall_side == 0 && cub->ray_dir_x > 0)
            draw_wall_pixel(cub, x, EAST);
        cub->start++;
    }
}