/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:56:55 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/18 13:44:18 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

/*Deniz' main*/
int main()
{
	t_prompt *prompt;
	t_cmmnds *cmd;
	t_cmmnds *cmd2;

	prompt = malloc(sizeof(t_prompt));
	cmd = malloc(sizeof(t_cmmnds));
	cmd2 = malloc(sizeof(t_cmmnds));
	prompt->cmd_list = ft_lstnew(cmd);
	ft_lstadd_back(&prompt->cmd_list, ft_lstnew(cmd2));
	cmd->prompt = prompt;
	cmd2->prompt = prompt;

	//example echo
	//cmd->full_command = malloc(sizeof((char*[]){"echo", /*"-n",*/ /*"hello world",*/ NULL})); //correct new lines
	//cmd->full_command = (char*[]){"echo", /*"-n",*/ /*"hello world",*/ NULL};

	//example ls
	cmd->full_command = malloc(sizeof((char*[]){"ls", "-l", NULL}));
	cmd->full_path = malloc(sizeof((char *)("/usr/bin/ls")));
	cmd->full_command = (char*[]){"ls", "-l", NULL};
	cmd->full_path = (char *)("/usr/bin/ls");

	/*not working: wc: 'standard input': Input/output error
	//example ls -l | wc -l (with above example ls)
	cmd2->full_command = malloc(sizeof((char*[]){"wc", "-l", NULL}));
	cmd2->full_path = malloc(sizeof((char *)("/usr/bin/wc")));
	cmd2->full_command = (char*[]){"wc", "-l", NULL};
	cmd2->full_path = (char *)("/usr/bin/wc");
	cmd->infile = 0;
	cmd->outfile = 1;
	cmd2->infile = 0;
	cmd2->outfile = 1;*/

	//example pwd
	cmd->full_command = malloc(sizeof((char*[]){"pwd", NULL}));
	cmd->full_command = (char*[]){"pwd", NULL};


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


