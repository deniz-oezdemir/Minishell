/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:34:24 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/08 13:39:08 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_builtin_nbr(t_cmddat *cmd)
{
	if (cmd->full_command == NULL) //@Leo: initialize full_command to NULL before parsing
		return (0);
	else if (!ft_strcmp(cmd->full_command[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd->full_command[0], "cd")) //use chdir function
		return (2);
	if (!ft_strcmp(cmd->full_command[0], "pwd"))
		return (3);
	else if (!ft_strcmp(cmd->full_command[0], "export"))
		return (4);
	else if (!ft_strcmp(cmd->full_command[0], "unset"))
		return (5);
	else if (!ft_strcmp(cmd->full_command[0], "env"))
		return (6);
	else if (!ft_strcmp(cmd->full_command[0], "exit"))
		return (7);
	return (0);
}

int	execute_builtin(t_cmddat *cmd, int n, int forked)
{
	int	val;

	(void)forked;
	val = 0; //Leo added this to silence warning
	if (n == 1)
		val = cstm_echo(cmd);
	else if (n == 2)
		val = cstm_cd(cmd);
	else if (n == 3)
		val = cstm_pwd(cmd);
	/*else if (n == 4)
		val = cstm_export(cmd);*/
	else if (n == 5)
		val = cstm_unset(cmd);
	else if (n == 6)
		val = cstm_env(cmd);
	else if (n == 7)
		val = cstm_exit(cmd);
	/*else
		val = 127; //127: command to execute could not be found*/
	/*if (forked)
	{
		cstm_lstiter(...);
		exit_ms(...);
	}*/
	return (val);
}
