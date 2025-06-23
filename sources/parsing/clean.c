/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:38:27 by vihane            #+#    #+#             */
/*   Updated: 2025/06/22 21:40:24 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int close_window(t_cub3d *cub3d)
{
    if (cub3d->mlx_ptr && cub3d->win_ptr)
    {
        mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
        cub3d->win_ptr = NULL;
    }
    if (cub3d->mlx_ptr)
    {
        mlx_destroy_display(cub3d->mlx_ptr);
        free(cub3d->mlx_ptr);
        cub3d->mlx_ptr = NULL;
    }
    return (0);
}
