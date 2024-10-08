/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:22:52 by ecarlier          #+#    #+#             */
/*   Updated: 2024/09/16 19:52:16 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	lexer(t_prompt *prompt)
{
	prompt->input_string = readline("minishell> ");
	collect_grbg(prompt, prompt->input_string);
	signals_non_interactive();
	add_history(prompt->input_string);
	if (prompt->input_string == NULL)
	{
		prompt->stop = 1;
		exit_ms(0, prompt);
		return ;
	}
	if (ft_strlen(prompt->input_string) <= 0
		|| is_only_space(prompt->input_string))
	{
		prompt->stop = 1;
		return ;
	}
	prompt->input_string = handle_spaces(prompt, prompt->input_string, 0, 0);
	prompt->commands = split_input(prompt->input_string, prompt);
	if (prompt->commands == NULL)
	{
		prompt->stop = 1;
	}
	if (prompt->stop != 1)
		prompt->commands = expander(prompt, prompt->commands, prompt->envp);
}
