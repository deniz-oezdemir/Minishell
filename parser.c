/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:41 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/19 18:20:41 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Iterate over the two-dimensional array
Whenever a redirection is found, check the type of redirection and retrieve a file descriptor containing the info we need as the infile
Check that the file descriptor that has been opened is valid (!= -1) and continue
If a pipe is found, add a new node to the list of commands
In all other cases add whatever words are found to the argument list (argv) we call full_cmd
*/
/*
 typedef struct s_cmddat
{
	char		**full_command;
	char		*full_path;
	int			infile;
	int			outfile;
	//t_uni		*uni;
	//int			broken;
}	t_cmddat;
*/
/*
prompt->commands
["ls", "-l", "|", "grep", "'file.txt'", ]
*/
void	parser(t_prompt *prompt)
{
	t_cmddat	*ptr;
	//int	create_new_node;

	ptr = init_struct();
	//create_new_node = 1;
	while (prompt->commands)
	{

	}


}

static t_cmddat	*init_struct(void)
{
	t_cmddat	*ptr;

	ptr = malloc(sizeof(t_cmddat));
	if (!ptr)
		return (NULL);
	ptr->full_command = NULL;
	ptr->full_path = NULL;
	ptr->infile = STDIN_FILENO;
	ptr->outfile = STDOUT_FILENO;
	return (ptr);
}
