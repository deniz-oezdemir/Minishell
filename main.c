/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:56:55 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/11 21:27:40 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>


/*
	ARGC MUST BE 1
*/
int	main(int argc, char *argv[], char **envp)
{
	t_prompt	prompt;

	(void)argv;

	if (argc == 1)
	{
		init_prompt_struct(prompt, envp);
	}


	//launch_minishell(&prompt);


	// for (int i = 0; envp[i] != NULL; i++) {
    //     printf("%s\n", envp[i]);
    // }
    // return 0;
}


// void	launch_minishell(t_prompt prompt)
// {
// 	//todo
// }


