/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ignore_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:31:44 by vihane            #+#    #+#             */
/*   Updated: 2025/07/15 12:30:12 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_ignore_spaces(char *str)
{
	int		i;
	char	*new;

	i = ft_strlen(str) - 2;
	while (i >= 0 && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i--;
	str[i + 1] = '\0';
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	new = ft_strdup(&str[i]);
	free(str);
	if (!new)
		return (NULL);
	return (new);
}
