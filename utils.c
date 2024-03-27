/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:31:31 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/27 18:44:07 by ecarlier         ###   ########.fr       */
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



void	print_err_msg(char *cmd, char *msg) //replace with below print_err_msg_lng if possible
{
	if (!msg)
		return ;
	ft_putstr_fd("mish: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

int print_err_msg_lng(char *cmd, char *msg, char *arg) //different -> compare all err msgs with bash
{
	//check arg, msg, cmd != NULL necessary?
	ft_putstr_fd("mish: ", 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	if (msg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
	}
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putstr_fd("\n", 2);
	return (1);
}
