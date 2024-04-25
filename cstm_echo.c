/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:50:56 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/25 11:46:00 by denizozd         ###   ########.fr       */
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
	/*if (cmd_data->prompt->nbr_cmds > 1 && cmd_data->lst_pos + 1 == cmd_data->prompt->nbr_cmds) //if there are multiple commands and echo is last cmd
	{
		close(cmd_data->infile);
		return (0);
	}*/
	/*if (cmd_data->infile != 0) //if pipe before echo - but could also be redirects!! also true for export! -> need pipe before flag? ///@Deniz: instead IDEA: function that iterates through command list and assigns every cmd_struct it's position in the cmd_list -> if echo is not the first cmd, there is a piupe infront of it
	{
		//close(cmd_->infile);
		//cmd- = 1;
		exitstatus = 1; // or return 1?
		return (0);
	}*/
	if (cmd_data->full_command[1] == NULL)
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
