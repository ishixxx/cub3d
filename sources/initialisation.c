/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:18:26 by vihane            #+#    #+#             */
/*   Updated: 2025/06/11 23:12:16 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    data_init(int argc, char **argv, t_cub3d *cub3d)
{
    (void) argc;
    (void) *argv;
    ft_memset(cub3d, 0, sizeof(t_cub3d));
    cub3d->mlx_ptr = mlx_init();
    if (!cub3d->mlx_ptr)
    {
        ft_putstr_fd(ERR_MLX, 2);
        exit(EXIT_FAILURE);
    }
    cub3d->win_ptr = mlx_new_window(cub3d->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
    if (cub3d->win_ptr == NULL)
    {
        ft_putstr_fd(ERR_WIN, 2);
        exit(EXIT_FAILURE);
    }
}

int parse_cub_file(const char *filename, t_cub3d *cub3d)
{
    if (!filename || !cub3d)
    {
        ft_putstr_fd(ERR_NO_MAP, 2);
        return (EXIT_FAILURE);
    }
}