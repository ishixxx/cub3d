/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:48:16 by vgalmich          #+#    #+#             */
/*   Updated: 2025/07/09 14:16:45 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* fonction qui recupere la couleur d'un pixel a la position (x, y) dans une
image donne */
/*
int get_color(t_cub3d *cub, int x, int y, int i)
{
    (void)i; // comment utiliser ce parametre ?
    int     bytes_per_pixel; // convertion des bits par pixel en octets
    int     offset; // calcul de l'offset dans l'image
    char    *pixel_address; // adresse du pixel cible

    bytes_per_pixel = cub->image.bpp / 8;
    offset = y * cub->image.line_size + x * bytes_per_pixel;
    pixel_address = cub->image.addr + offset;
    return (*(int *)pixel_address); // lit la couleur (en int) a cette adresse
}
    */

/* fonction qui retourne la couleur d'un pixel situe aux coordonnees x,y dans
une texture donnee par l'index i */
int get_color(t_cub3d *cub, int x, int y, int i)
{
    t_img *tex;

    if (i == NORTH)
        tex = &cub->texture_north;
    else if (i == SOUTH)
        tex = &cub->texture_south;
    else if (i == WEST)
        tex = &cub->texture_west;
    else if (i == EAST)
        tex = &cub->texture_east;
    else
        return 0;

    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return 0;

    int bytes_per_pixel = tex->bpp / 8;
    int offset = y * tex->line_size + x * bytes_per_pixel;
    char *pixel_address = tex->addr + offset;

    return *(unsigned int *)pixel_address;
}
