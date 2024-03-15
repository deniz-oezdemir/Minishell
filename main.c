/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:56:55 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/15 13:22:38 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

/*Deniz' main*/
int main()
{
	t_prompt *prompt;
	t_cmmnds *cmd;

	prompt = malloc(sizeof(t_prompt));
	cmd = malloc(sizeof(t_cmmnds));
	prompt->cmd_list = malloc(sizeof(t_list));
	prompt->cmd_list->content = cmd;
	cmd->prompt = prompt;

	//example echo
	//cmd->full_command = malloc(sizeof((char*[]){"echo", /*"-n",*/ /*"hello world",*/ NULL})); //correct new lines
	//cmd->full_command = (char*[]){"echo", /*"-n",*/ /*"hello world",*/ NULL};

	//example ls
	cmd->full_command = malloc(sizeof((char*[]){"ls", "-l", NULL}));
	cmd->full_command = (char*[]){"ls", "-l", NULL};
	cmd->full_path = malloc(sizeof((char *)("/usr/bin/ls")));
	cmd->full_path = (char *)("/usr/bin/ls");
	execute_cmds(prompt);

	return (0);
}

/*
	ARGC MUST BE 1
*/
/*Leo's main*/
/*int	main(int argc, char *argv[], char **envp)
{
	t_prompt	*prompt;

	(void)argv;

	if (argc == 1)
	{
		init_prompt_struct(prompt, envp);
	}

	launch_minishell(&prompt);
	return (0);
}

void	launch_minishell(t_prompt *prompt)
{
	siganl(SIGINT, sigint_handler);
	while (1)
	{
		pause;
	}
}
*/


