/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:22:52 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/18 18:31:29 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*take an input sequence of characters and divide them into "tokens*/

/*
	Ceci est une phrase de test
	Ceci est "une phrase avec" des guillemets
	Mot1|Mot2|Mot3
*/

/* */
void	lexer(t_prompt *prompt)
{
	char **arr;
	prompt->input_string = readline("minishell> ");

	// if (!prompt->input_string)
	// 	exit_minishelll

	arr = split_input(prompt->input_string);
	print_str_array(arr);
	intern_split(arr);



}
