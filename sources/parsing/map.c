/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:18:00 by vihane            #+#    #+#             */
/*   Updated: 2025/06/12 23:18:29 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int parse_map_border(char *line, t_cub3d *cub3d)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != ' ')
        {
            ft_putstr_fd(ERR_MAP, 2);
            return (0);
        }
        i++;
    }
    if (i > cub3d->map_width)
        cub3d->map_width = i;
    return (1);
}