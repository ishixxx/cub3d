/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:48:16 by vgalmich          #+#    #+#             */
/*   Updated: 2025/07/02 22:32:47 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* fonction qui recupere la couleur d'un pixel a la position (x, y) dans une
image donne */

int get_color(t_cub3d *cub, int x, int y, int i)
{
    int     bytes_per_pixel; // convertion des bits par pixel en octets
    int     offset; // calcul de l'offset dans l'image
    char    *pixel_address; // adresse du pixel cible

    bytes_per_pixel = cub->image[i].bpp / 8;
    offset = y * cub->image[i].line_size + x * bytes_per_pixel;
    pixel_address = cub->image[i].addr + offset;
    return (*(int *)pixel_address); // lit la couleur (en int) a cette adresse
}