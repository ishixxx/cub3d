/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:18:26 by vihane            #+#    #+#             */
/*   Updated: 2025/06/10 14:21:36 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    data_init(int argc, char **argv, t_cub3d *cub3d)
{
    ft_memset(cub3d, 0, sizeof(t_cub3d));
    cub3d->mlx_ptr = mlx_init();
    if (!cub3d->mlx_ptr)
    {
        ft_putstr_fd(ERR_MLX, 2);
        exit(EXIT_FAILURE);
    }
    
}