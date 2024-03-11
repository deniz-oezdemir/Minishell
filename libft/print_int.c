/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:38:50 by ecarlier          #+#    #+#             */
/*   Updated: 2023/11/22 23:01:38 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_unsigned_fd(unsigned int n, int fd)
{
	if (n > 9)
	{
		ft_putnbr_unsigned_fd((n / 10), fd);
		ft_putnbr_unsigned_fd((n % 10), fd);
	}
	else
		ft_putchar_fd((n + 48), fd);
}

static int	get_len(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len += 1;
		n = -n;
	}
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	get_len_unsigned(unsigned int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	print_int(va_list args)
{
	int	i;
	int	number;

	i = 0;
	number = va_arg(args, int);
	ft_putnbr_fd(number, 1);
	i = get_len(number);
	return (i);
}

int	print_unsigned(va_list args)
{
	int				i;
	unsigned int	n;

	n = va_arg(args, unsigned int);
	ft_putnbr_unsigned_fd(n, 1);
	i = get_len_unsigned(n);
	return (i);
}
