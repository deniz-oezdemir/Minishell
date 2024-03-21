/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:22:52 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/21 18:43:26 by denizozd         ###   ########.fr       */
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

	// if (!prompt->input_string)
	// 	exit_minishelll
	prompt->input_string = add_space(prompt->input_string);
	prompt->commands= split_input(prompt->input_string);

	//
	//print_str_array(prompt->commands);

}
