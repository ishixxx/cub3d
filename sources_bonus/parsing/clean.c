/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:38:27 by vihane            #+#    #+#             */
/*   Updated: 2025/07/14 16:06:28 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_mlx(t_cub3d *cub3d)
{
	if (cub3d)
	{
		if (cub3d->image.data)
			mlx_destroy_image(cub3d->mlx_ptr, cub3d->image.data);
		if (cub3d->texture_north.data)
			mlx_destroy_image(cub3d->mlx_ptr, cub3d->texture_north.data);
		if (cub3d->texture_south.data)
			mlx_destroy_image(cub3d->mlx_ptr, cub3d->texture_south.data);
		if (cub3d->texture_west.data)
			mlx_destroy_image(cub3d->mlx_ptr, cub3d->texture_west.data);
		if (cub3d->texture_east.data)
			mlx_destroy_image(cub3d->mlx_ptr, cub3d->texture_east.data);
		if (cub3d->win_ptr)
			mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
		if (cub3d->mlx_ptr)
		{
			mlx_destroy_display(cub3d->mlx_ptr);
			free(cub3d->mlx_ptr);
		}
	}
}

int	close_game(t_cub3d *cub3d, char *msg)
{
	ft_printf("%s\n", msg);
	free_cub(cub3d);
	if (cub3d->mlx_ptr)
		free_mlx(cub3d);
	exit(1);
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

void	free_cub(t_cub3d *cub3d)
{
	if (cub3d->map)
		free_double_array(&cub3d->map);
	if (cub3d->line)
		free(cub3d->line);
	if (cub3d->map_width)
		free(cub3d->map_width);
	close(cub3d->fd);
}
