/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:22:52 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/20 13:48:05 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_only_space(const char *str)
{
	while (*str != '\0')
	{
		if (!isspace(*str))
			return (0);
		str++;
	}
	return (1);
}
/*take an input sequence of characters and divide them into "tokens*/

/*
test : echo hello
Before split : prompt.input_string = "echo hello"
after split : prompt.commands = [ "echo", "hello", NULL]
*/

void	lexer(t_prompt *prompt)
{

	prompt->input_string = readline("minishell> ");
	collect_grbg(prompt->input_string);
	signals_non_interactive();
	if (prompt->input_string == NULL)
	{
		prompt->stop = 1;
		exit_ms(0, prompt);
		return ;
	}
	if (ft_strlen(prompt->input_string) <= 0 || is_only_space(prompt->input_string))
	{
			prompt->stop = 1;
			return ;
	}
	prompt->input_string = add_space(prompt->input_string);
	prompt->commands = split_input(prompt->input_string, prompt);
	if (prompt->commands == NULL)
	{
		prompt->stop = 1;
		//free(prompt->input_string);
	}
	//print_str_array(prompt->commands);
	if (prompt->stop != 1)
		prompt->commands = expander(prompt->commands, prompt->envp);
}


