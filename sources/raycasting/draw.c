/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:04:20 by vgalmich          #+#    #+#             */
/*   Updated: 2025/06/28 19:44:57 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// coder la lecture des couleurs

// fonction pour dessiner un pixel de couleur dans une image memoire
void    draw_pixel(t_img *img, t_point p, int color)
{
    char    *pixel;
    int     x;
    int     y;

    x = (int)p.x;
    y = (int)p.y;
     // si les coordonnees depassent la fenetre -> on ne dessine pas
    if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return;
    // calcul de l'adresse memoire precise ou est stocke le pixel
    pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
    // on fait un cast pour pouvoir modifier un pixel ->
    // on ecrit 4 octets en une seule operation
    *(unsigned int *)pixel = color;
}


/* fonction qui calcule la hauteur du mur a dessiner en fonction de la
distance au mur (perp_wall_dist) et trouve les coordonnees verticales de
début et de fin pour cette colones */
void    compute_wall_slice(t_cub3d *cub, int *line_height, int *start, int *end)
{
    // calcul de la hauteur du mur projete a l'ecran
    *line_height = (int)cub->win_height / cub->ray.perp_wall_dist;
    // calcul du pointde depart vertical (debut du mur)
    *start = -(*line_height) / 2 * cub->win_height / 2;
    // si depassement, on coupe
    if (*start < 0)
        *start = 0;
    // calcul du point de fin vertical (fin du mur)
    *end = *line_height / 2 + cub->win_height / 2;
    if (*end >= cub->win_height)
        *end = cub->win_height - 1;
}

/* fonction qui prepare tous les parametres pour mapper correctement
une teture murale sur une colonne verticale de l'ecran, en fonction de
la ou le rayon a frappe le mur */
void    init_tex_mapping(t_cub3d *cub, int start, int line_height)
{
    // 1. calcul de la position de l'impact sur le mur
    if (cub->ray.wall_side == 0)
        cub->ray.wall_x = cub->player.pos.y + cub->ray.perp_wall_dist * cub->ray.ray_dir_y;
    else
         cub->ray.wall_x = cub->player.pos.x + cub->ray.perp_wall_dist * cub->ray.ray_dir_x;
    // 2. on garde la partie decimale pour localiser l'impact sur le mur
    cub->ray.wall_x -= floor(cub->ray.wall_x); // fonction mathematique qui retourne la + grande valeur entiere inferieure ou egale a un nb donne
    // 3. calcul la coordonnee texture_x (colonne de texture a prelever)
    cub->ray.tex_x = cub->ray.wall_x * 128; // 128 pixels de large pour la texture
    // 4. on ajuste texture_x si le mur est vu de l'autre cote
    if (cub->ray.wall_side == 0 && cub->ray.ray_dir_x > 0)
        cub->ray.tex_x = 128 - cub->ray.tex_x - 1;
    if (cub->ray.wall_side == 1 && cub->ray.ray_dir_y < 0)
        cub->ray.tex_x = 128 - cub->ray.tex_x - 1;
    // 5. calcul du pas de progression vertical dans la texture
    cub->ray.step = 1.0 * 128 / line_height;
    // 6. position initale dans la texture pour la premiere ligne affichee
    cub->ray.tex_pos = (start - cub->win_height / 2 + line_height / 2) * cub->ray.step;
}

/* fonction pour dessiner un pixel vertical de mur a l'ecran a la colonne x
avec la bonne couleur prelevee depuis la texture */
void    draw_wall_pixel(t_cub3d *cub, int x, int texture)
{
    int color;
    color = get_color(cub, cub->texture_x, cub->teture_y, texture);
    draw_pixel(cub, c, cub->start, color);
}

/* fonction qui trace une ligne verticale sur l'ecran representant un mur*/
void    draw_wall_column(t_cub3d *cub, int x)
{
    // 1. definir la hauteur et les limites de la colonne
    int line_height;
    compute_wall_slice(cub, &line_height, &cub->start, &cub->end);
    // 2. configurer les coordonnees de texture
    init_tex_mapping(cub, cub->start, line_height);
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