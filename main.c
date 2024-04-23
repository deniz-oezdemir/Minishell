/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:56:55 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/23 17:51:40 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exitstatus = 0; //somehow definition here needed, otherwise compile error-> read up on global variables

int	main(int argc, char *argv[], char **envp)
{
	t_prompt	*prompt;

	prompt = NULL;

	(void)argv;

	if (argc == 1)
	{
		prompt = ft_calloc(1, sizeof(t_prompt)); //gc not possible here as gc needs gc_list to be allocated -> prompt needs seperate free at exit
		init_prompt_struct(prompt, envp);
	}
	launch_minishell(prompt);
	return (0);
}

void	launch_minishell(t_prompt *prompt)
{
	//signals_interactive(); //@Leo: is this needed here and in the while loop?

	while (1)
	{
		signals_interactive();
		// signal(SIGINT, &sig_handler_rl);
		// signal(SIGQUIT, SIG_IGN);
		prompt->stop = 0;
		lexer(prompt);
		if (prompt->stop == 0)
			parser(prompt, 0, 0);
		//print_cmd_list(prompt->cmd_list);
		if (cstm_lstsize(prompt->cmd_list) > 1 && prompt->stop == 0)
			pipe_infile_outfile(prompt->cmd_list); //@Deniz: not gc'ed within pipe_infile_outfile as does not leak
		//print_cmd_list(prompt->cmd_list);
		if (!prompt->stop)
			execute_cmds(prompt);
		prompt->cmd_list = NULL; //this works but why @Leo
	}
}

/* no garbage collection for below function as it does not leak
set outfile to write end of pipe
set infile to read end of pipe */
void	pipe_infile_outfile(t_node *cmd_lst)
{
	int *pip;

	while (cmd_lst->next != NULL)
	{
		pip = ft_calloc(2, sizeof(int));
		if (!pip)
			return ;
		if (pipe(pip) == -1)
		{
			free(pip);
			return ;
		}
		if (cmd_lst->data->outfile == 1)
			cmd_lst->data->outfile = pip[1];
		else
			close(pip[1]);
		if (cmd_lst->next->data->infile == 0) //LEO ADDED THIS
			cmd_lst->next->data->infile = pip[0];
		else
			close(pip[0]);
		cmd_lst=cmd_lst->next;
		free(pip);
	}
	return ;
}

