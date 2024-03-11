/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:26:53 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/11 21:45:32 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "signal.h"
# include <sys/types.h>

# include "./libft/libft.h"


/*
	*input_string :
	**commands :
	*cmd_list :

	**envp : Up-to-date array containing keys and values for the shell environment

	pid : Process ID of the minishell instance

*/

typedef struct s_prompt
{
	char		*input_string;
	char		**commands;
	t_list		*cmd_list;
	char		**envp;
	pid_t		pid;
	//int			stop;
}	t_prompt;


/*
	**full_command; argv

	*full_path; If not a builtin, first available path for the executable denoted by argv[0] from the PATH variable

	infile; Which file descriptor to read from when running a command (defaults to stdin)

	outfile; Which file descriptor to write to when running a command (defaults to stdout
*/
typedef struct s_cmmnds
{
	char		**full_command;
	char		*full_path;
	int			infile;
	int			outfile;
	//t_uni		*uni;
	//int			broken;
}	t_cmmnds;


#endif
