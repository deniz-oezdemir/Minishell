/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:56:55 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/05 17:27:41 by ecarlier         ###   ########.fr       */
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
		execute_cmds(prompt);
		if (prompt->commands)
			free_char_array(prompt->commands);
		cstm_lstclear(&prompt->cmd_list, (void (*)(void *))free_node_list);

	}
}
