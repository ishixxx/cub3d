/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:16:54 by vihane            #+#    #+#             */
/*   Updated: 2025/07/17 16:29:24 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	check_texture(t_cub3d *cub3d, char *line)
{
	t_img	*img;

	if (!ft_strncmp(line, "NO ", 3) && !cub3d->texture_north.data)
		img = &cub3d->texture_north;
	else if (!ft_strncmp(line, "SO ", 3) && !cub3d->texture_south.data)
		img = &cub3d->texture_south;
	else if (!ft_strncmp(line, "WE ", 3) && !cub3d->texture_west.data)
		img = &cub3d->texture_west;
	else if (!ft_strncmp(line, "EA ", 3) && !cub3d->texture_east.data)
		img = &cub3d->texture_east;
	else
		close_game(cub3d, ERR_DUP_TEXTURE);
	if (ft_strlen(line) < 4 || ft_strncmp(line + ft_strlen(line) - 4, ".xpm",
			4) != 0)
		close_game(cub3d, ERR_XPM);
	while (ft_isspace(*(line + 3)))
		line++;
	img->data = mlx_xpm_file_to_image(cub3d->mlx_ptr, line + 3, &img->width,
			&img->height);
	if (!img->data)
		close_game(cub3d, ERR_XPM_IMG);
	img->addr = mlx_get_data_addr(img->data, &img->bpp, &img->line_size,
			&img->endian);
	if (!img->addr)
		close_game(cub3d, ERR_TEXTURE_ADDR);
}
