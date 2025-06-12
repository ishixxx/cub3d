/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:18:44 by vihane            #+#    #+#             */
/*   Updated: 2025/06/12 23:20:55 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_color_line_valid(char *line)
{
    if (!line || ft_strlen(line) < 2)
        return 0;
    return (ft_strncmp("F ", line, 2) == 0 ||
            ft_strncmp("C ", line, 2) == 0);
}

int parse_color_value(char *line)
{
    int r;
    int g;
    int b;
    char **colors;
    colors = ft_split(line, ',');
    if (!colors || !colors[0] || !colors[1] || !colors[2])
    {
        ft_putstr_fd(ERR_COLOR, 2);
        return (-1);
    }
    r = ft_atoi(colors[0]);
    g = ft_atoi(colors[1]);
    b = ft_atoi(colors[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        ft_putstr_fd(ERR_COLOR, 2);
        return (-1);
    }
    free(colors[0]);
    free(colors[1]);
    free(colors[2]);
    free(colors);
    return ((r << 16) | (g << 8) | b);
}