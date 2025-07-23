/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:47:36 by vihane            #+#    #+#             */
/*   Updated: 2025/07/23 18:05:59 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

int		ft_readline(int fd, char **remaining_buffer);
char	*ft_removelinefromstatic(char **remaining_buffer);
char	*set_the_buffer_line(int fd, char **remaining_buffer);
char	*get_next_line(int fd);
char	*ft_strcat2(char *remaining_buffer, char *buffer, int result);

char	*ft_fill_line(int fd, char **fourre_merde);
char	*ft_strcat_custom(char *fourre_merde, char *buff, int res);
int		ft_readline(int fd, char **fourre_merde);
char	*ft_removelinefromstatic(char **fourre_merde);
char	*ft_strcat_custom(char *fourre_merde, char *buff, int res);
char	*ft_fill_line(int fd, char **fourre_merde);

#endif
