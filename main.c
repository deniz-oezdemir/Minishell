/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:56:55 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/21 18:42:08 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

/*
	ARGC MUST BE 1
*/

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
		parser(prompt);
	}
}
