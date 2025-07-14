/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:44:54 by vihane            #+#    #+#             */
/*   Updated: 2025/07/14 16:05:15 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_map_texture_and_color(t_cub3d *cub3d)
{
	if (!cub3d->texture_north.data || !cub3d->texture_south.data
		|| !cub3d->texture_west.data || !cub3d->texture_east.data)
		close_game(cub3d, ERR_NO_TEXTURE);
	if (cub3d->floor.r == -1 || cub3d->ceiling.r == -1)
		close_game(cub3d, ERR_NO_FLOOR);
	if (cub3d->floor.g == -1 || cub3d->ceiling.g == -1)
		close_game(cub3d, ERR_NO_CEILING);
	if (cub3d->floor.b == -1 || cub3d->ceiling.b == -1)
		close_game(cub3d, ERR_NO_CEILING);
	if (!cub3d->map || !cub3d->map[0])
		close_game(cub3d, ERR_NO_MAP);
	parse_map_second(cub3d);
}

int	map_texture_and_color(t_cub3d *cub3d, char *line)
{
	if (line_is_empty(cub3d, line))
		return (0);
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		check_texture(cub3d, line);
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
	{
		if (!ft_strncmp(line, "F ", 2) && cub3d->floor.r == -1)
			check_color(cub3d, &cub3d->floor, line);
		else if (!ft_strncmp(line, "C ", 2) && cub3d->ceiling.r == -1)
			check_color(cub3d, &cub3d->ceiling, line);
		else
			close_game(cub3d, ERR_DUP_COLOR);
	}
	else
		close_game(cub3d, INVALID_COLOR_OR_TEXTURE);
	return (1);
}

int	parse_map_first(t_cub3d *cub3d, char *file)
{
	int	n;

	n = 0;
	cub3d->fd = open(file, O_RDONLY);
	if (cub3d->fd == -1)
		close_game(cub3d, ERR_OPEN);
	cub3d->line = get_next_line(cub3d->fd);
	while (cub3d->line)
	{
		n++;
		if (!cub3d->texture_north.data || !cub3d->texture_south.data
			|| !cub3d->texture_east.data || !cub3d->texture_west.data
			|| cub3d->floor.r == -1 || cub3d->ceiling.r == -1)
		{
			cub3d->line = ft_ignore_spaces(cub3d->line);
			map_texture_and_color(cub3d, cub3d->line);
		}
		else
			keep_map(cub3d, file, cub3d->line, n);
		free(cub3d->line);
		cub3d->line = get_next_line(cub3d->fd);
	}
	close(cub3d->fd);
	check_map_texture_and_color(cub3d);
	return (1);
}
