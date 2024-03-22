/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:50:56 by denizozd          #+#    #+#             */
/*   Updated: 2024/03/22 15:06:50 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cstm_echo(t_cmddat *cmd_data)
{
	int	nl;
	int	i;

	nl = 1;
	i = 1;
	if (cmd_data == NULL)
		return (1);
	if (cmd_data->full_command[1] == NULL)
		return (ft_putstr_fd("\n", cmd_data->outfile), 1);
	if (!ft_strcmp(cmd_data->full_command[1], "-n")) //different
	{
		nl = 0;
		i += 1;
	}
	while (cmd_data->full_command[i])
	{
		ft_putstr_fd(cmd_data->full_command[i], cmd_data->outfile);
		i += 1;
		if (cmd_data->full_command[i] != NULL) //Necessity of space depends on how @Leo parses the input
			ft_putstr_fd(" ", cmd_data->outfile);
	}
	if(nl)
		ft_putstr_fd("\n", cmd_data->outfile);
	return (0);
}
