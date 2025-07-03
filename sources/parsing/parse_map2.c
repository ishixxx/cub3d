/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:20:49 by vihane            #+#    #+#             */
/*   Updated: 2025/07/03 14:27:02 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    check_map_inside(t_cub3d *cub3d, char c, int i, int j)
{
    if (ft_isin(c, "NSEW"))
    {
        if (c == ' ')
            return ;
        close_game(cub3d, ERR_MAP);
    }
}

void    check_space(t_cub3d *cub3d, int i, int j)
{
    if (cub3d->map[i][j] == ' ')
    {
        if (i < cub3d->map_height - 1 && !is_null(cub3d->map, i + 1, j) && 
            cub3d->map[i + 1][j] != ' ' && cub3d->map[i + 1][j] != '1')
            close_game(cub3d, ERR_CLOSE_MAP);
        if (i > 0 && !is_null(cub3d->map, i - 1, j) && 
            cub3d->map[i - 1][j] != ' ' && cub3d->map[i - 1][j] != '1')
            close_game(cub3d, ERR_CLOSE_MAP);
        if (j > 0 && !is_null(cub3d->map, i, j - 1) && 
            cub3d->map[i][j - 1] != ' ' && cub3d->map[i][j - 1] != '1')
            close_game(cub3d, ERR_CLOSE_MAP);
        if (!is_null(cub3d->map, i, j + 1) && 
            cub3d->map[i][j + 1] != ' ' && cub3d->map[i][j + 1] != '1')
            close_game(cub3d, ERR_CLOSE_MAP);
    }
}

void    parse_map_second(t_cub3d *cub3d)
{
    cub3d->i = 0;
    while (cub3d->map[cub3d->i])
    {
        cub3d->j = 0;
        while (cub3d->map[cub3d->i][cub3d->j])
        {
            if (cub3d->map[cub3d->i][cub3d->j] == ' ')
                check_space(cub3d, cub3d->i, cub3d->j);
            if ((cub3d->i == 0 || cub3d->i == cub3d->map_height - 1)
                && (cub3d->map[cub3d->i][cub3d->j] != '1'
                && cub3d->map[cub3d->i][cub3d->j] != ' '))
                close_game(cub3d, ERR_CLOSE_MAP);
            if ((cub3d->j == 0 || !cub3d->map[cub3d->i][cub3d->j + 1])
                && (cub3d->map[cub3d->i][cub3d->j] != '1'
                && cub3d->map[cub3d->i][cub3d->j] != ' '))
                close_game(cub3d, ERR_CLOSE_MAP);
            if (cub3d->i > 0 && cub3d->i < cub3d->map_height - 1 && cub3d->j > 0)
                check_map_inside(cub3d, cub3d->map[cub3d->i][cub3d->j], cub3d->i, cub3d->j);
            cub3d->j++;
    }
    cub3d->i++;
    }
    if (cub3d->player.pos.x == -1 || cub3d->player.pos.y == -1)
        close_game(cub3d, ERR_NO_PLAYER); 
}