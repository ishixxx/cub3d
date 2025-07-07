/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:04:49 by vihane            #+#    #+#             */
/*   Updated: 2025/07/07 16:40:41 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	check_format_type(va_list args, const char format,
		int *writtencharacter)
{
	if (format == 'c')
	{
		(*writtencharacter)++;
		ft_print_char(va_arg(args, int));
	}
	else if (format == 's')
		ft_print_string(va_arg(args, char *), writtencharacter);
	else if (format == 'p')
		ft_print_point(va_arg(args, unsigned long long), writtencharacter);
	else if (format == 'd' || format == 'i')
		ft_print_int(va_arg(args, int), writtencharacter);
	else if (format == 'u')
		ft_print_unsigned(va_arg(args, unsigned int), writtencharacter);
	else if (format == 'x' || format == 'X')
		ft_print_hex(va_arg(args, unsigned int), format, writtencharacter);
	else if (format == '%')
	{
		ft_print_char(format);
		(*writtencharacter)++;
	}
}

int	ft_printf(const char *format, ...)
{
	int		writtencharacter;
	va_list	args;

	va_start(args, format);
	writtencharacter = 0;
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format != '%')
		{
			ft_print_char(format[0]);
			writtencharacter++;
		}
		else
			check_format_type(args, *++format, &writtencharacter);
		format++;
	}
	va_end(args);
	return (writtencharacter);
}
