/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:38:27 by vihane            #+#    #+#             */
/*   Updated: 2025/07/07 14:28:55 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	close_game(void *param, char *msg)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	printf("%s\n", msg); // rajouter fonction ft_printf
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
	free_map(cub3d);
	exit(EXIT_FAILURE);
	return (0);
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
	int	i;

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
