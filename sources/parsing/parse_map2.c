/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:20:49 by vihane            #+#    #+#             */
/*   Updated: 2025/07/23 17:37:57 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_map_inside(t_cub3d *cub3d, char c, int i, int j)
{
	if (ft_isin(c, "NSEW"))
	{
		if (cub3d->player.pos.x != -1)
			close_game(cub3d, ERR_DUP_PLAYER);
		cub3d->player.pos.x = j + 0.5;
		cub3d->player.pos.y = i + 0.5;
		set_direction1(cub3d, c);
		set_direction2(cub3d, c);
	}
	else if (!ft_isin(c, " 01"))
		close_game(cub3d, ERR_MAP);
}

void	set_direction1(t_cub3d *cub3d, char c)
{
	if (c == 'N')
	{
		cub3d->player.plane.x = 0.66;
		cub3d->player.plane.y = 0.0;
	}
	else if (c == 'S')
	{
		cub3d->player.plane.x = -0.66;
		cub3d->player.plane.y = 0.0;
	}
	else if (c == 'E')
	{
		cub3d->player.plane.x = 0.0;
		cub3d->player.plane.y = 0.66;
	}
	else if (c == 'W')
	{
		cub3d->player.plane.x = 0.0;
		cub3d->player.plane.y = -0.66;
	}
}

void	set_direction2(t_cub3d *cub3d, char c)
{
	if (c == 'N')
	{
		cub3d->player.dir.x = 0.0;
		cub3d->player.dir.y = -1.0;
	}
	else if (c == 'S')
	{
		cub3d->player.dir.x = 0.0;
		cub3d->player.dir.y = 1.0;
	}
	else if (c == 'E')
	{
		cub3d->player.dir.x = 1.0;
		cub3d->player.dir.y = 0.0;
	}
	else if (c == 'W')
	{
		cub3d->player.dir.x = -1.0;
		cub3d->player.dir.y = 0.0;
	}
}

void	check_space(t_cub3d *cub3d, int i, int j)
{
	if (cub3d->map[i][j] == ' ')
	{
		if (i < cub3d->map_height - 1 && !is_null(cub3d->map, i + 1, j)
			&& cub3d->map[i + 1][j] != ' ' && cub3d->map[i + 1][j] != '1')
			close_game(cub3d, ERR_CLOSE_MAP);
		if (i > 0 && !is_null(cub3d->map, i - 1, j) && cub3d->map[i
				- 1][j] != ' ' && cub3d->map[i - 1][j] != '1')
			close_game(cub3d, ERR_CLOSE_MAP);
		if (j > 0 && !is_null(cub3d->map, i, j - 1) && cub3d->map[i][j
			- 1] != ' ' && cub3d->map[i][j - 1] != '1')
			close_game(cub3d, ERR_CLOSE_MAP);
		if (!is_null(cub3d->map, i, j + 1) && cub3d->map[i][j + 1] != ' '
			&& cub3d->map[i][j + 1] != '1')
			close_game(cub3d, ERR_CLOSE_MAP);
	}
}

void	parse_map_second(t_cub3d *cub)
{
	cub->i = 0;
	while (cub->map[cub->i])
	{
		cub->j = 0;
		while (cub->map[cub->i][cub->j])
		{
			if (cub->map[cub->i][cub->j] == ' ')
				check_space(cub, cub->i, cub->j);
			if ((cub->i == 0 || cub->i == cub->map_height - 1)
				&& (cub->map[cub->i][cub->j] != '1'
				&& cub->map[cub->i][cub->j] != ' '))
				close_game(cub, ERR_CLOSE_MAP);
			if ((cub->j == 0 || !cub->map[cub->i][cub->j + 1])
				&& (cub->map[cub->i][cub->j] != '1'
					&& cub->map[cub->i][cub->j] != ' '))
				close_game(cub, ERR_CLOSE_MAP);
			if (cub->i > 0 && cub->i < cub->map_height - 1 && cub->j > 0)
				check_map_inside(cub, cub->map[cub->i][cub->j], cub->i, cub->j);
			cub->j++;
		}
		cub->i++;
	}
	if (cub->player.pos.x == -1 || cub->player.pos.y == -1)
		close_game(cub, ERR_NO_PLAYER);
}
