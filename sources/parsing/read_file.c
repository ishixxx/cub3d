/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:07:32 by vihane            #+#    #+#             */
/*   Updated: 2025/07/04 15:58:21 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**read_file(int fd, t_cub3d *cub3d)
{

	char	buffer[100];
	
	(void)cub3d; // parametre non utilise

	if (read(fd, buffer, sizeof(buffer) - 1) == -1)
	{
		ft_putstr_fd(ERR_FILE, 2);
		return (NULL);
	}
	buffer[sizeof(buffer) - 1] = '\0';
	close(fd);
	return (NULL);
}
