/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:38:27 by vihane            #+#    #+#             */
/*   Updated: 2025/06/24 19:36:01 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	close_game(t_cub3d *cub3d, char *msg)
{
	ft_printf(msg);
	if (cub3d->mlx_ptr && cub3d->win_ptr)
	{
		mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
		cub3d->win_ptr = NULL;
	}
	if (cub3d->mlx_ptr)
	{
		mlx_destroy_display(cub3d->mlx_ptr);
		free(cub3d->mlx_ptr);
		cub3d->mlx_ptr = NULL;
	}
	free_map(cub3d->map);
	exit(EXIT_FAILURE);
}

void	free_map(t_cub3d *cub3d)
{
	int	i;

	if (cub3d->map)
	{
		i = 0;
		while (i < cub3d->map_height)
		{
			free(cub3d->map[i]);
			i++;
		}
		free(cub3d->map);
		cub3d->map = NULL;
	}
}

void	free_double_array(char ***array)
{
	int		i;

	i = 0;
	if (!array)
		return ;
	while ((*array)[i])
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}
