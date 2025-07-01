/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:07:39 by vihane            #+#    #+#             */
/*   Updated: 2025/07/01 14:17:56 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_isin(char c, char *str)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

int	is_null(char **map, int i, int j)
{
	int	k;

	k = 0;
	while (map[i] && map[i][k])
		k++;
	if (k <= j)
		return (1);
	return (0);
}

void	ignore_space(char **line)
{
	char	*start;

	start = *line;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	if (start != *line)
		*line = start;
}

int	line_is_empty(t_cub3d *cub3d, char *line)
{
	cub3d->i = 0;
	while (ft_isspace(line[cub3d->i]))
		cub3d->i++;
	if (!line[cub3d->i])
		return (1);
	return (0);
}

int	handle_coma(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == ',')
			i++;
		str++;
	}
	return (i);
}
