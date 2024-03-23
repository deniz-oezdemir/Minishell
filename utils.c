/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:31:31 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/23 13:00:19 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_len_arr(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}

int	ft_isspace(int c)
{
	//printf("enters ft_isspace");
	if (c == ' ' || (c >= 9 && c <= 13))
	{
		//printf("LE char est '%c' \n et la valeur retournee 1", c);
		return (1);
	}

	else
	{
		//printf("LE char est '%c' \n et la valeur retournee 0", c);
		return (0);
	}

}



/*@deniz do you use this ? you need to add ft_ otherise you use the original one and not sure we can ???*/
int	strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	print_err_msg(char *cmd, char *msg)
{
	if (!msg)
		return ;
	ft_putstr_fd("ms: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}
