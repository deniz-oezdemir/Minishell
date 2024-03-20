/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:26:53 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/20 21:26:38 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "signal.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>

# include "./libft/libft.h"

extern int	exitstatus;

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

//@Leo: we need this pointer to the main struct
//@Leo: rename to t_cmddat as each node stores a single command's data?
/*
/!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\
@deniz don't forget to remane it
/!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\


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

typedef struct s_cmmnds
{
	char		**full_command;
	char		*full_path;
	int			infile;
	int			outfile;
	t_prompt		*prompt;
	//int			broken;
}	t_cmmnds;

/*	main	*/
void	launch_minishell(t_prompt prompt);

/*	init	*/
t_prompt	init_prompt_struct(t_prompt *prompt, char **envp);
int	init_env(t_prompt *prompt, char **env);

/*	signal_handler	*/
void	sigint_handler(int signum);
void	handle_sig_quit(int n);

/*	utils.c	*/
size_t	get_len_arr(char **array);
int	strcmp(const char *s1, const char *s2);
void	print_err_msg(char *cmd, char *msg);

/*	builtins.c	*/
int	get_builtin_nbr(t_cmmnds *cmd);
int	execute_builtin(t_cmmnds *cmd, int n, int forked);

/*	cstm_echo.c	*/
int	cstm_echo(t_cmmnds *cmd);

/*	cstm_pwd.c	*/
int	cstm_pwd(t_cmmnds *cmd_data);

/*	cstm_env.c	*/
int	cstm_env(t_cmmnds *cmd_data);

/*	cstm_exit	*/
int	cstm_exit(t_cmmnds *cmd_data);
int	is_only_digits(char *s);

/*	cstm_unset	*/
int	cstm_unset(t_cmmnds *cmd_data);
size_t get_env_len(const char *s);

/*	end.c	*/
void	exit_ms(int exitstatus, t_prompt *prompt);

/*	exec.c	*/
int	execute_cmds(t_prompt *prompt);

#endif
