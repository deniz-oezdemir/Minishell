/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:56:55 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/01 18:20:32 by ecarlier         ###   ########.fr       */
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

	launch_minishell(prompt); //@Leo: Deniz deleted & in front of prompt as compilation warning
	return (0);
}

void	launch_minishell(t_prompt *prompt)
{
	// signal(SIGINT, &sigint_handler);
	while (1)
	{
		lexer(prompt);
		if (prompt->commands == NULL)
			continue;
		if (prompt->commands)
			add_history(prompt->input_string);
		parser(prompt);
		execute_cmds(prompt);
		//free between commands
	}
}
