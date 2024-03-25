/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:44:46 by denizozd          #+#    #+#             */
/*   Updated: 2024/03/25 17:33:13 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_executable(t_cmddat cmd_data)
{
	
}

void wait_update_exitstatus(t_prompt *prompt)
{
	int	tmp_exitstatus;
	int	child_status;
	t_cmddat *last;

	tmp_exitstatus = -1;
	last = ft_lstlast(prompt->cmd_list)->content;
	if (waitpid(prompt->pid, &child_status, 0) != -1 && WIFEXITED(child_status)) //Wait for first child process to terminate; if it exits normally (not by a signal), update temp_exitcode with the exit status of the child process.
		tmp_exitstatus = WEXITSTATUS(child_status);
	while(waitpid(-1, &child_status, 0) != -1) //wait for any child processes to terminate
		continue ; //continue until all child processes are terminated
	if (tmp_exitstatus != -1) //if exitstatus changed during wait
		exitstatus = tmp_exitstatus;
	if (exitstatus == 130)
		ft_putstr_fd("\n", 2); //if program was terminated by a SIGINT signal //different
	if (exitstatus == 131) //if program was terminated by a SIGQUIT signal -> maybe use SIGQUIT instead f 131
		ft_putstr_fd("Quit\n", 2);
	if (last->broken != 0) //@Leo: initialized broken?
		exitstatus = last->broken; //@Leo: maybe we can rename broken to fail_exitstatus, or similar
	else if (!last->full_path && !get_builtin_nbr(last))
		exitstatus = 127;
	else if (last->full_path && !get_builtin_nbr(last) && (!access(last->full_path, F_OK) && access(last->full_path, X_OK < 0))) //F_OK checks that file exists, X_OK checks that file executable
		exitstatus = 126;
	return ;
}

void	cls_fds(void *content)
{
	t_cmddat	*cmd_data;

	cmd_data = (t_cmddat *)content;
	if (cmd_data->infile != -1 && cmd_data->infile != 0) //verify what else then -1, 0, 1 in- and outfile can be
		close(cmd_data->infile);
	if (cmd_data->outfile != -1 && cmd_data->outfile != 1)
		close(cmd_data->outfile);
}

void	run_cmd(void *content)
{
	t_cmddat *cmd_data;

	cmd_data = (t_cmddat *)content;

	/*if (cmd_data->prompt->stop)
		return ;*/
	if (!is_executable(cmd_data, get_builtin_nbr(cmd_data))) //@Deniz: write is_executable
		return ;
	cmd_data->prompt->pid = fork();
	if (cmd_data->prompt->pid == -1) //fork error
		return ;
	if (cmd_data->prompt->pid == 0) //fork success
	{
		if (get_builtin_nbr(cmd_data))
			execute_builtin(cmd_data, get_builtin_nbr(cmd_data), 1);
		dup2(cmd_data->infile, 0);
		dup2(cmd_data->outfile, 1);
		ft_lstiter(cmd_data->prompt->cmd_list, cls_fds); //why here also? because forked?
		execve(cmd_data->full_path, cmd_data->full_command, cmd_data->prompt->envp);
		close(0);
		close(1);
		exit_ms(2, cmd_data->prompt); //why exitstatus 2?
	}
	return (0);
}

int	execute_cmds(t_prompt *prompt)
{
	t_cmddat	*cmd_data;

	if (!prompt->cmd_list)
		return (0);
	//signal(SIGQUIT, &handle_sig_quit); @Leo: What does ths do?
	cmd_data = prompt->cmd_list->data;
	if(ft_lstsize(prompt->cmd_list) == 1 && get_builtin_nbr(cmd_data)) //change t_node to t_lst such that we can use libft functions
	{
		exitstatus = execute_builtin(cmd_data, get_builtin_nbr(cmd_data), 0); //@Deniz: continue writing execute_builtin
		ft_lstiter(prompt->cmd_list, cls_fds); //ft_lstiter necessary? if only one cmd, only cls_fds once should be enough
	}
	else
	{
		ft_lstiter(prompt->cmd_list, run_cmd);
		ft_lstiter(prompt->cmd_list, cls_fds);
		wait_update_exitstatus(prompt);
	}
	return (0);
}
