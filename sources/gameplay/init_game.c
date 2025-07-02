/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:41:31 by vgalmich          #+#    #+#             */
/*   Updated: 2025/07/02 22:41:31 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int init_game(t_cub3d *cub)
{
    if (!cub->image.addr)
    {
        ft_putstr_fd("Error\nImage not initialized.\n", 2);
        return (1);
    }
    // Hook principal : appel a render a chaque frame
    mlx_loop_hook(cub->mlx_ptr, render_3D_scene, cub);
    // reste des hook ?
    // boucle graphique
    mlx_loop(cub->mlx_ptr);
    return (0);
}