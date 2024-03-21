/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:26:53 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/21 17:29:52 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "signal.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <readline/readline.h>

# include "./libft/libft.h"

extern int	exitstatus;


/*Standard file descriptors.
STDIN_FILENO	0	 Standard input.
STDOUT_FILENO	1	 Standard output.
STDERR_FILENO	2	 Standard error output.
*/
typedef struct s_node t_node;
typedef struct s_prompt t_prompt;
typedef struct s_cmddat t_cmddat;

//@Leo: each nodes content in cmd_list must be of type t_prompt
/*
	*input_string :
	**commands :
	*cmd_list :

	**envp : Up-to-date array containing keys and values for the shell environment

	pid : Process ID of the minishell instance

*/
/*modif t_list with t_node*/
typedef struct s_prompt
{
	char		*input_string;
	char		**commands;
	t_node		*cmd_list;
	char		**envp;
	pid_t		pid;
	//int			stop;
}	t_prompt;


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
		command (defaults to stdout)
*/

typedef struct s_cmddat
{
	char		**full_command;
	char		*full_path;
	int			infile;
	int			outfile;
	t_prompt		*prompt;
	//int			broken;
}	t_cmddat;


/* debug utils*/
void print_char_array(const char arr[]);
void print_str_array(char **arr);
void print_command_list(t_node *head);
void print_cmd_list(const t_node *head);

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
void	print_err_msg(char *cmd, char *msg);

/*	builtins.c	*/
int	get_builtin_nbr(t_prompt *cmd);
int	execute_builtin(t_prompt *cmd, int n, int forked);

/*	cstm_echo.c	*/
int	cstm_echo(t_prompt *cmd);

/*	cstm_pwd.c	*/
int	cstm_pwd(t_prompt *cmd_data);

/*	cstm_env.c	*/
int	cstm_env(t_prompt *cmd_data);

/*	cstm_exit	*/
int	cstm_exit(t_prompt *cmd_data);
int	is_only_digits(char *s);

/*	cstm_unset	*/
int	cstm_unset(t_prompt *cmd_data);
size_t get_len_env(const char *s);

/*	end.c	*/
void	exit_ms(int exitstatus, t_prompt *prompt);

/*	exec.c	*/
int	execute_cmds(t_prompt *prompt);
int	strcmp(const char *s1, const char *s2);
int	ft_isspace(int c);

/*	lexer.c*/
void	lexer(t_prompt *prompt);


/* split*/
char	**split_input(char *str);
char	**ft_split(char const *s, char c);
char *add_space(char *str);

/*	parser*/
void	parser(t_prompt *prompt);
char	**fill_arr(char **prompt, int i, int len);

/* list_utils */
void	add_node_to_list(t_node **head, t_cmddat *data);
int	ft_listsize(t_node *lst);

#endif
