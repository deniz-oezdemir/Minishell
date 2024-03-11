/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:21:46 by ecarlier          #+#    #+#             */
/*   Updated: 2023/11/13 12:42:02 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t len)
{
	unsigned int	i;
	unsigned char	*p;

	p = str;
	i = 0;
	while (i < len)
	{
		p[i] = 0;
		i++;
	}
	return ;
}
