/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:10:20 by vihane            #+#    #+#             */
/*   Updated: 2025/07/07 16:40:22 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

size_t	ft_point_len(uintptr_t nbr)
{
	size_t	i;

	i = 0;
	while (nbr)
	{
		i++;
		nbr = nbr / 16;
	}
	return (i);
}

void	ft_put_point(uintptr_t nbr)
{
	if (nbr >= 16)
	{
		ft_put_point(nbr / 16);
		ft_put_point(nbr % 16);
	}
	else
	{
		if (nbr <= 9)
			ft_putchar_fd((nbr + '0'), 1);
		else
			ft_putchar_fd((nbr - 10 + 'a'), 1);
	}
}

void	ft_print_point(unsigned long long ptr, int *writtencharacter)
{
	if (ptr == 0)
		(*writtencharacter) += write (1, "(nil)", 5);
	else
	{
		(*writtencharacter) += write (1, "0x", 2);
		ft_put_point(ptr);
		(*writtencharacter) += ft_point_len(ptr);
	}
}
