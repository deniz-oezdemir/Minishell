/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:44:46 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/08 11:26:41 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_executable(t_cmddat *cmd_data)
{
	int builtin;

	builtin = get_builtin_nbr(cmd_data);
	if (cmd_data->file_open_error > 0) //different
	{
		exitstatus = cmd_data->file_open_error;
		return (0);
	}
	if (!builtin && !cmd_data->full_path) //different
	{
		if (cmd_data->full_command[0]) //understand why only for this case print
			print_err_msg_lng(cmd_data->full_command[0], "command not found", NULL); //different
		exitstatus = 127;
		return (0);
	}
	else if (!builtin && cmd_data->full_path && (!access(cmd_data->full_path, F_OK) && access(cmd_data->full_path, X_OK) == -1))
	{
		if(cmd_data->full_command[0]) //different
			print_err_msg_lng(cmd_data->full_command[0], "permission denied", NULL);
		exitstatus = 126;
		return (0);
	}
	return (1);
}

void wait_update_exitstatus(t_prompt *prompt)
{
	int	tmp_exitstatus;
	int	child_status;
	t_cmddat *last;

	tmp_exitstatus = -1;
	last = cstm_lstlast(prompt->cmd_list)->data;
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
	if (last->file_open_error != 0) //@Leo: initialized broken?
		exitstatus = last->file_open_error; //@Leo: maybe we can rename broken to fail_exitstatus, or similar
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
	if (cmd_data->infile != -1 && cmd_data->infile != 0) //verify what else other than -1, 0, 1 in- and outfile can be @Leo: parsing
		close(cmd_data->infile);
	if (cmd_data->outfile != -1 && cmd_data->outfile != 1)
		close(cmd_data->outfile);
}

void	run_cmd(void *content)
{
	t_cmddat *cmd_data;

	cmd_data = (t_cmddat *)content;
		printf("c3.2.1\n");
	// //LEO uncommented because needed this
	// if (cmd_data->prompt->stop == 1)
	// 	return ;
	//
	if (!is_executable(cmd_data)) //@Deniz: write is_executable //different
		return ;
		printf("c3.2.2\n");
		print_cmddat(cmd_data);
		printf("pid: %ld\n", cmd_data->prompt->pid);
	cmd_data->prompt->pid = 0;//fork(); //seg fault: somehow can not assign anything to pid -> because *prompt is not initialized
		printf("c3.2.3\n");
	if (cmd_data->prompt->pid == -1) //fork error
		return ;
		printf("c3.2.4\n");
	if (cmd_data->prompt->pid == 0) //fork success
	{
		if (get_builtin_nbr(cmd_data))
			execute_builtin(cmd_data, get_builtin_nbr(cmd_data), 1);
			printf("3.2.5\n");
		dup2(cmd_data->infile, 0);
		dup2(cmd_data->outfile, 1);
		cstm_lstiter(cmd_data->prompt->cmd_list, cls_fds); //why here also? because forked?
		execve(cmd_data->full_path, cmd_data->full_command, cmd_data->prompt->envp);
		close(0);
		close(1);
		exit_ms(2, cmd_data->prompt); //why exitstatus 2?
	}
	return ;
}

int	execute_cmds(t_prompt *prompt)
{
	t_cmddat	*cmd_data;

	if (!prompt->cmd_list)
		return (0);
	//signal(SIGQUIT, &handle_sig_quit); @Leo: What does ths do?
	cmd_data = prompt->cmd_list->data;
		printf("c1\n");
	if(cstm_lstsize(prompt->cmd_list) == 1 && get_builtin_nbr(cmd_data)) //change t_node to t_lst such that we can use libft functions
	{
			printf("c2\n");
		exitstatus = execute_builtin(cmd_data, get_builtin_nbr(cmd_data), 0); //@Deniz: continue writing execute_builtin
			printf("c3\n");
		cstm_lstiter(prompt->cmd_list, cls_fds); //cstm_lstiter necessary? if only one cmd, only cls_fds once should be enough
	}
	else
	{
			printf("c3\n");
		cstm_lstiter(prompt->cmd_list, run_cmd);
			printf("c4\n");
		cstm_lstiter(prompt->cmd_list, cls_fds);
		wait_update_exitstatus(prompt);
	}
	return (0);
}
