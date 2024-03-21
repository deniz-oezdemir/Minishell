/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:50:56 by denizozd          #+#    #+#             */
/*   Updated: 2024/03/21 17:41:35 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cstm_echo(t_cmddat *cmd)
{
	int	nl;
	int	i;

	nl = 1;
	i = 1;
	if (cmd == NULL)
		return (1);
	if (cmd->full_command[1] == NULL)
		return (ft_putstr_fd("\n", cmd->outfile), 1);
	if (!strcmp(cmd->full_command[1], "-n")) //different
	{
		nl = 0;
		i += 1;
	}
	while (cmd->full_command[i])
	{
		ft_putstr_fd(cmd->full_command[i], cmd->outfile);
		i += 1;
		if (cmd->full_command[i] != NULL) //Necessity of space depends on how @Leo parses the input
			ft_putstr_fd(" ", cmd->outfile);
	}
	if(nl)
		ft_putstr_fd("\n", cmd->outfile);
	return (0);
}
