/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:16:54 by vihane            #+#    #+#             */
/*   Updated: 2025/06/12 23:17:38 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_texture_line_valid(char *line)
{
    if (!line || ft_strlen(line) < 3)
        return 0;
    return (ft_strncmp("NO ", line, 3) == 0 ||
            ft_strncmp("SO ", line, 3) == 0 ||
            ft_strncmp("WE ", line, 3) == 0 ||
            ft_strncmp("EA ", line, 3) == 0);
}

int parse_textures_line(char *line, t_texture *texture)
{
    char *path;
    
    while (*line && *line != ' ')
        line++;
    while (*line == ' ')
        line++;
    path = ft_strtrim(line, " \n");
    if (ft_strncmp(path, "NO ", 3) == 0)
         texture->north = path;
    else if (ft_strncmp(path, "SO ", 3) == 0)
        texture->south = path;
    else if (ft_strncmp(path, "WE ", 3) == 0)
        texture->west = path;
    else if (ft_strncmp(path, "EA ", 3) == 0)
        texture->east = path;
    else
    {
        ft_putstr_fd(ERR_TEXTURE, 2);
        free(path);
        return (0);
    }

}