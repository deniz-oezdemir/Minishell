/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:26:53 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/15 09:01:37 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "signal.h"
# include <sys/types.h>
# include <stdlib.h>
# include <readline/readline.h>

# include "./libft/libft.h"

extern int	exitcode;

//@Leo: each nodes content in cmd_list must be of type t_cmmnds
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


//@Leo: rename to t_cmddat as each node stores a single command's data?
//done V
/*
	**full_command;
		Array containing command's parts

	*full_path;
		If not a builtin, first available path for the
		executable denoted by argv[0] from the PATH variable

	infile;
		Which file descriptor to read from when running
		a command (defaults to stdin)

	outfile;
		Which file descriptor to write to when running a
		command (defaults to stdout
*/

typedef struct s_cmddat
{
	char		**full_command;
	char		*full_path;
	int			infile;
	int			outfile;
	//t_uni		*uni;
	//int			broken;
}	t_cmddat;

/*	main	*/
void	launch_minishell(t_prompt *prompt);

/*	init	*/
void	init_prompt_struct(t_prompt *prompt, char **envp);
int	init_env(t_prompt *prompt, char **env);

/*	signal_handler	*/
void	sigint_handler(int signum);
void	handle_sig_quit(int n);

/*	utils.c	*/
size_t	get_len_arr(char **array);
int	strcmp(const char *s1, const char *s2);
int	ft_isspace(int c);

/*	lexer.c*/
void	lexer(t_prompt *prompt);


/* split*/
char	**split_input(char *str);
#endif
