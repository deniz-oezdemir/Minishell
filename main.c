/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:56:55 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/09 20:15:29 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exitstatus = 0; //somehow definition here needed, otherwise compile error-> read up on global variables

int	main(int argc, char *argv[], char **envp)
{
	t_prompt	*prompt;

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
	signals_interactive(); //theo

	// signal(SIGINT, &sigint_handler);
	// signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		lexer(prompt);
		// if (prompt->commands == NULL)
		// 	continue;
		if (prompt->commands)
			add_history(prompt->input_string);
		parser(prompt);
		pipe_infile_outfile(prompt->cmd_list);
		print_cmd_list(prompt->cmd_list);
		execute_cmds(prompt);

		if (prompt->commands)
			free_char_array(prompt->commands);

		cstm_lstclear(&prompt->cmd_list, clear_cmmdat_lst);

	}
}

void	pipe_infile_outfile(t_node *cmd_lst)
{
	int *pip;

	while (cmd_lst)
	{
		pip = ft_calloc(2, sizeof(int));
		if (!pip)
			return ;
		if (pipe(pip) == -1)
		{
			free(pip);
			return ;
		}
		if (cstm_lstsize(cmd_lst) != 1)
		{
			if (cmd_lst->data->outfile == 1)
				cmd_lst->data->outfile = pip[1];
			else
				close(pip[1]);
			cmd_lst->next->data->infile = pip[0];
			cmd_lst=cmd_lst->next;
		}
		free(pip);
	}
	return ;
}

