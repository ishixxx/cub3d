/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:29:20 by vihane            #+#    #+#             */
/*   Updated: 2025/07/02 19:13:05 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int keypress(int keycode, t_cub3d *cub3d)
{
    if (keycode == LEFT || keycode == RIGHT)
        close_window(cub3d);
    
}

int keyrealease(int keycode, t_cub3d *cub3d)
{

}

int close_window(t_cub3d *cub3d)
{
    mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
    free_map(cub3d);
    exit(0);
}