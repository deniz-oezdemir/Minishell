/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:26:53 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/11 18:43:49 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"


/*
input_string :
commands :
cmd_list :
envp :
pid :

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
