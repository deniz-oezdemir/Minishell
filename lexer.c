/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:22:52 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/19 16:45:56 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*take an input sequence of characters and divide them into "tokens*/


void	lexer(t_prompt *prompt)
{

	prompt->input_string = readline("minishell> ");

	// if (!prompt->input_string)
	// 	exit_minishelll
	prompt->input_string = add_space(prompt->input_string);
	prompt->commands= split_input(prompt->input_string);
	print_str_array(prompt->commands);

}
