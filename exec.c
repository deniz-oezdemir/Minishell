/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:44:46 by denizozd          #+#    #+#             */
/*   Updated: 2024/03/21 17:41:35 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_cmd(t_cmddat *cmd_data)
{
	//test not-builtin -> make new example in main, comment out old one
	//execve(cmd_data->full_path, cmd_data->full_command, cmd_data->prompt->envp);

	/*if (cmd_data->prompt->stop)
		return (0);*/
	/*if (!is_executable(cmd_data, get_builtin_nbr(cmd_data)))
		return (0);*/
	cmd_data->prompt->pid = fork();
	if (cmd_data->prompt->pid == -1) //fork error
		return (1);
	if (cmd_data->prompt->pid == 0) //fork success
	{
		if (get_builtin_nbr(cmd_data))
			execute_builtin(cmd_data, get_builtin_nbr(cmd_data), 1);
		dup2(cmd_data->infile, 0);
		dup2(cmd_data->outfile, 1);
		/*ft_lstiter...*/
		execve(cmd_data->full_path, cmd_data->full_command, cmd_data->prompt->envp);
		close(0);
		close(1);
		//exit_ms(...);
	}
	return (0);
}

int	execute_cmds(t_prompt *prompt)
{
	t_cmddat	*cmd_data;

	if (!prompt->cmd_list)
		return (0);
	//signal(SIGQUIT, &handle_sig_quit);

	//	build execute one command first to test
	cmd_data = prompt->cmd_list->content;
	if(ft_lstsize(prompt->cmd_list) == 1 && get_builtin_nbr(cmd_data))
	{
		exitstatus = execute_builtin(cmd_data, get_builtin_nbr(cmd_data), 0); //@Deniz: continue writing execute_builtin
		//ft_lstiter(prompt->cmd_list, close_fds()); //write close_fds
	}
	else //for now only not-builtin, expand later to execute multiple commands
	{
		run_cmd(cmd_data); //different
		waitpid(prompt->pid, NULL, 0);
	}
	return 0;
}
