/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:56:55 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/25 16:15:59 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exitstatus = 0;

int	main(int argc, char *argv[], char **envp)
{
	t_prompt	*prompt;

	prompt = NULL;
	(void)argv;
	if (argc == 1)
	{
		prompt = ft_calloc(1, sizeof(t_prompt));
		init_prompt_struct(prompt, envp);
	}
	launch_minishell(prompt);
	return (0);
}

void	launch_minishell(t_prompt *prompt)
{
	while (1)
	{
		signals_interactive();
		prompt->stop = 0;
		lexer(prompt);
		if (prompt->stop == 0)
			parser(prompt, 0, 0);
		if (cstm_lstsize(prompt->cmd_list) > 1 && prompt->stop == 0)
			pipe_infile_outfile(prompt->cmd_list);
		if (!prompt->stop)
			execute_cmds(prompt);
		prompt->cmd_list = NULL;
	}
}

/* no garbage collection for below function as it does not leak
set outfile to write end of pipe
set infile to read end of pipe */
void	pipe_infile_outfile(t_node *cmd_lst)
{
	int	*pip;

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
		if (cmd_lst->next->data->infile == 0)
			cmd_lst->next->data->infile = pip[0];
		else
			close(pip[0]);
		cmd_lst = cmd_lst->next;
		free(pip);
	}
	return ;
}
