/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:52:26 by ecarlier          #+#    #+#             */
/*   Updated: 2023/11/17 16:04:47 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(long n);
static char	*fill_the_array(int len, char *dest, int n );

static int	get_len(long n)
{
	size_t	len;

	len = 0;
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

static	char	*fill_the_array(int len, char *dest, int n )
{
	int	i;

	i = 0;
	if (n < 0)
	{
		dest[0] = '-';
		n = n * (-1);
		i = 1;
	}
	dest[len] = '\0';
	len -= 1;
	while (len >= i)
	{
		dest[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	char	*dest;
	size_t	len;
	long	num;

	if (n == -2147483648)
		return (dest = ft_strdup("-2147483648")); 
	if (n == 0)
		return (dest = ft_strdup("0"));
	num = n;
	len = get_len(num);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	dest = fill_the_array(len, dest, num);
	return (dest);
}
