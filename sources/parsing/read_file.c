/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:07:32 by vihane            #+#    #+#             */
/*   Updated: 2025/06/24 19:49:36 by vihane           ###   ########.fr       */
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

static void	free_line(char **line)
{
	size_t	i;

	i = 0;
	if (line[i])
		free(line[i++]);
	free(line);
}

static void	ft_erase_newline(char *line)
{
	size_t	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}
