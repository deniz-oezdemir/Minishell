/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:50:56 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/24 15:05:42 by ecarlier         ###   ########.fr       */
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
	if (cmd_data->full_cmd[1] == NULL)
		return (ft_putstr_fd("\n", cmd_data->outfile), 1);
	if (!ft_strcmp(cmd_data->full_cmd[1], "-n")) //different
	{
		nl = 0;
		i += 1;
	}
	while (cmd_data->full_cmd[i])
	{
		ft_putstr_fd(cmd_data->full_cmd[i], cmd_data->outfile);
		i += 1;
		if (cmd_data->full_cmd[i] != NULL)
			ft_putstr_fd(" ", cmd_data->outfile);
	}
	if(nl)
		ft_putstr_fd("\n", cmd_data->outfile);
	return (0);
}
