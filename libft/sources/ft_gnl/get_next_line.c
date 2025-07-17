/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:10:14 by vihane            #+#    #+#             */
/*   Updated: 2025/07/17 20:14:58 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_strcat2(char *remaining_buffer, char *buffer, int result)
{
	int		i;
	int		src;
	char	*new_buffer;

	i = 0;
	src = 0;
	while (remaining_buffer[i])
		i++;
	new_buffer = malloc((i + result + 1) * sizeof(char));
	if (!new_buffer)
		return (NULL);
	i = 0;
	while (remaining_buffer[i])
	{
		new_buffer[i] = remaining_buffer[i];
		i++;
	}
	while (buffer[src])
		new_buffer[i++] = buffer[src++];
	new_buffer[i] = '\0';
	free(remaining_buffer);
	return (new_buffer);
}

int	ft_readline(int fd, char **remaining_buffer)
{
	int		read_bytes;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes > 0)
	{
		buffer[read_bytes] = '\0';
		*remaining_buffer = ft_strcat2(*remaining_buffer, buffer, read_bytes);
		if (!*remaining_buffer)
			return (free(buffer), -1);
	}
	if (read_bytes < 0 ||*remaining_buffer[0] == '\0')
		read_bytes = -1;
	free(buffer);
	return (read_bytes);
}

char	*set_the_buffer_line(int fd, char **remaining_buffer)
{
	int	i;
	int	read_line;

	while (1)
	{
		i = 0;
		while ((*remaining_buffer)[i])
		{
			if ((*remaining_buffer)[i] == '\n')
				return (ft_removelinefromstatic(remaining_buffer));
			i++;
		}
		read_line = ft_readline(fd, remaining_buffer);
		if (read_line < 0)
			return (NULL);
		if (read_line == 0)
			break ;
	}
	return (ft_removelinefromstatic(remaining_buffer));
}

char	*ft_removelinefromstatic(char **remaining_buffer)
{
	char	*static_buffer;
	int		i;
	int		x;
	char	*read_line;
	int		z;

	static_buffer = *remaining_buffer;
	i = 0;
	while (static_buffer[i] && static_buffer[i] != '\n')
		i++;
	if (static_buffer[i] == '\n')
		i++;
	read_line = malloc(i + 1);
	if (!read_line)
		return (NULL);
	ft_memcpy(read_line, static_buffer, i);
	read_line[i] = '\0';
	x = 0;
	z = i;
	while (static_buffer[z++])
		x++;
	ft_memmove(static_buffer, static_buffer + i, x);
	static_buffer[x] = '\0';
	*remaining_buffer = static_buffer;
	return (read_line);
}


char	*get_next_line(int fd)
{
	static char buffer_static[4095][BUFFER_SIZE + 1];
	char *all;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	all = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!all)
		return (NULL);
	ft_memcpy(all, buffer_static[fd], ft_strlen(buffer_static[fd]));
	all[ft_strlen(buffer_static[fd])] = '\0';
	if (!buffer_static[fd][0])
		all[0] = '\0';
	line = set_the_buffer_line(fd, &all);
	if (!line)
	{
		if (all)
			(free(all), all = NULL);
		return (NULL);
	}
	ft_memcpy(buffer_static[fd], all, ft_strlen(all));
	buffer_static[fd][ft_strlen(all)] = '\0';
	(free(all), all = NULL);
	return (line);
}

