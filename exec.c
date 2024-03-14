/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:44:46 by denizozd          #+#    #+#             */
/*   Updated: 2024/03/14 11:27:10 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmds(t_prompt *prompt)
{
	t_cmmnds	*cmd; //assumption: single command is a string

	if (!prompt->cmd_list)
		return (0);
	signal(SIGQUIT, &handle_sig_quit);

	//	build execute one command first to test
	cmd = &prompt->cmd_list->content; //difference
	if(ft_lstsize(prompt->cmd_list) == 1 && get_builtin_nbr(cmd))
	{
		exitcode = execute_builtin(cmd, get_builtin_nbr(cmd), 0); //@Deniz: continue writing execute_builtin
		ft_lstiter(prompt->cmd_list, close_fds()); //write close
	}
	else
	{
	//	build execute multiple commands
	}
}
