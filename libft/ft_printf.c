/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:17:39 by ecarlier          #+#    #+#             */
/*   Updated: 2023/11/23 15:00:54 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_type(char c, va_list args)
{
	int	i;

	i = 0;
	if (c == 's')
		i = print_string(args);
	else if (c == 'i' || c == 'd')
		i = print_int(args);
	else if (c == 'u')
		i = print_unsigned(args);
	else if (c == 'c')
		i = print_char(args);
	else if (c == 'x' || c == 'X')
		i = print_hexa(args, c);
	else if (c == 'p')
		i = print_pointeur(args);
	else if (c == '%')
	{
		i = 1;
		ft_putchar_fd('%', 1);
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		total_count;
	va_list	args;

	total_count = 0;
	va_start(args, format);
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			ft_putchar_fd(format[i], 1);
			total_count += 1;
		}
		else
		{
			i++;
			total_count += check_type(format[i], args);
		}
		i++;
	}
	va_end(args);
	return (total_count);
}
