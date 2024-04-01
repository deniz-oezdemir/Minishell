/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:22:52 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/01 19:40:34 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*take an input sequence of characters and divide them into "tokens*/

/*
test : echo hello
Before split : prompt.input_string = "echo hello"
after split : prompt.commands = [ "echo", "hello", NULL]
*/

void	lexer(t_prompt *prompt)
{

	prompt->input_string = readline("minishell> ");

	if (prompt->input_string == NULL)
	{
		printf("no str\n");
		exit_ms(0, prompt);

	}
	prompt->input_string = add_space(prompt->input_string);
	prompt->commands = split_input(prompt->input_string);
	//print_str_array(prompt->commands);
	if (prompt->commands == NULL)
	{
		prompt->stop = 1;
		free(prompt->input_string);
	}
	else
		print_str_array(prompt->commands);

	//verifier avant expander que les quotes soient bien fermees
	if (prompt->stop != 1)
		prompt->commands = expander(prompt->commands, prompt->envp);
	// print_str_array(prompt->commands);

}
