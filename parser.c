/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:41 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/19 16:58:47 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
	int	create_new_node;

	ptr = init_struct();
	create_new_node = 1;



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
