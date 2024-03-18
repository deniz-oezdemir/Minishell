/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:22:52 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/15 16:30:22 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*take an input sequence of characters and divide them into "tokens*/
void	lexer(t_prompt *prompt)
{
	prompt->input_string = readline("minishell> ");

	// if (!prompt->input_string)
	// 	exit_minishelll
	//printf(" %s\n", prompt->input_string);
	split_input(prompt->input_string);

}
