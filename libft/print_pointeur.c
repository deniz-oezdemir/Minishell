/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointeur.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:07:36 by ecarlier          #+#    #+#             */
/*   Updated: 2023/11/23 15:12:31 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int static	ft_putchar_count_ptr(char c)
{
	write(1, &c, 1);
	return (1);
}

static void	ft_puthex_ptr(uintptr_t n, int *count)
{
	if (n < 10)
	{
		*count += ft_putchar_count_ptr(n + '0');
	}
	else if (n < 16)
	{
		*count += ft_putchar_count_ptr('a' + (n - 10));
	}
	else
	{
		ft_puthex_ptr(n / 16, count);
		ft_puthex_ptr(n % 16, count);
	}
}

int	print_pointeur(va_list args)
{
	void	*ptr;
	int		count;

	ptr = va_arg(args, void *);
	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		count = 5;
	}
	else
	{
		count = 2;
		write(1, "0x", 2);
		ft_puthex_ptr((uintptr_t)ptr, &count);
	}
	return (count);
}
