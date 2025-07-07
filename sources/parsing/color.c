/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:18:44 by vihane            #+#    #+#             */
/*   Updated: 2025/07/07 14:28:57 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_color(t_cub3d *cub3d, t_color *color, char *line)
{
	char	**split;

	if (handle_coma(line) != 2)
		close_game(cub3d, ERR_COLOR);
	split = ft_split(line + 2, ',');
	if (!split || !split[0] || !split[1] || !split[2])
	{
		ft_free_split(split);
		close_game(cub3d, ERR_COLOR);
	}
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	ft_free_split(split);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		close_game(cub3d, ERR_COLOR);
}

// rajouter
void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
