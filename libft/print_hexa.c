/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:59:08 by ecarlier          #+#    #+#             */
/*   Updated: 2023/11/23 12:04:52 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int static	ft_putchar_count(char c)
{
	write(1, &c, 1);
	return (1);
}

static void	ft_puthex(unsigned int n, char c, int *count)
{
	if (n < 10)
	{
		*count += ft_putchar_count(n + '0');
	}
	else if (n < 16)
	{
		if (c == 'x')
			*count += ft_putchar_count('a' + (n - 10));
		else
			*count += ft_putchar_count('A' + (n - 10));
	}
	else
	{
		ft_puthex(n / 16, c, count);
		ft_puthex(n % 16, c, count);
	}
}

int	print_hexa(va_list args, char c)
{
	int				count;
	unsigned int	n;

	count = 0;
	n = va_arg(args, int);
	ft_puthex(n, c, &count);
	return (count);
}
