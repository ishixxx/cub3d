/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:07:32 by vihane            #+#    #+#             */
/*   Updated: 2025/07/04 14:09:11 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
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
	*/

char **read_file(int fd, t_cub3d *cub3d)
{
    char buffer[4096];
    ssize_t bytes_read;
    char *file_content;
    char **lines;

    (void)cub3d;

    file_content = malloc(1);
    if (!file_content)
        return NULL;
    file_content[0] = '\0';

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
    {
        buffer[bytes_read] = '\0';
        char *temp = malloc(strlen(file_content) + bytes_read + 1);
        if (!temp)
        {
            free(file_content);
            return NULL;
        }
        strcpy(temp, file_content);
        strcat(temp, buffer);
        free(file_content);
        file_content = temp;
    }

    if (bytes_read < 0)
    {
        free(file_content);
        ft_putstr_fd(ERR_FILE, 2);
        return NULL;
    }
    lines = ft_split(file_content, '\n');  // Conversion en tableau de lignes
    free(file_content);
    return lines;
}
