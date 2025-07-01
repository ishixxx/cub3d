/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:07:32 by vihane            #+#    #+#             */
/*   Updated: 2025/07/01 14:11:15 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**read_file(int fd, t_cub3d *cub3d)
{
	char	buffer[100];

	if (read(fd, buffer, sizeof(buffer) - 1) == -1)
	{
		ft_putstr_fd(ERR_FILE, 2);
		return (NULL);
	}
	close(fd);
	buffer[sizeof(buffer) - 1] = '\0';
}
