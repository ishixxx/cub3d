/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:16:54 by vihane            #+#    #+#             */
/*   Updated: 2025/07/04 16:08:21 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void check_texture(t_cub3d *cub3d, char *line)
{
	t_img *img;

	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
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
	while (*line && !ft_isspace(*line))
		line++;
	while (*line && ft_isspace(*line))
		line++;
	if (ft_strlen(line) < 4 || ft_strncmp(line + ft_strlen(line) - 4, ".xpm", 4) != 0)
		close_game(cub3d, ERR_XPM);
	img->data = mlx_xpm_file_to_image(cub3d->mlx_ptr, line, &img->width, &img->height);
	if (!img->data)
		close_game(cub3d, ERR_XPM_IMG);
	img->addr = mlx_get_data_addr(img->data, &img->bpp, &img->line_size, &img->endian);
	if (!img->addr)
		close_game(cub3d, ERR_TEXTURE_ADDR);
}
