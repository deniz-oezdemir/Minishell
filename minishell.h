/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:26:53 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/22 16:06:34 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <dirent.h>
# include <unistd.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/ioctl.h>


# include "./libft/libft.h"

extern int exitstatus;

/*Standard file descriptors.
STDIN_FILENO	0	 Standard input.
STDOUT_FILENO	1	 Standard output.
STDERR_FILENO	2	 Standard error output.
*/
typedef struct s_node t_node;
typedef struct s_prompt t_prompt;
typedef struct s_cmddat t_cmddat;
typedef struct s_grbg t_grbg;


//@Leo: each nodes content in cmd_list must be of type t_prompt
/*
	*input_string :
	**commands :
	*cmd_list :

	**envp : Up-to-date array containing keys and values for the shell environment

	pid : Process ID of the minishell instance

*/

//@Leo: we need stop, but i don't know how it's initialized, etc.
/*modif t_list with t_node*/
typedef struct s_prompt
{
	char		*input_string;
	char		**commands;
	t_node		*cmd_list;
	char		**envp;
	pid_t		pid;
	int			stop;
	t_grbg		*grbg_lst;
}	t_prompt;

typedef struct s_node
{
	t_cmddat	*data;
	struct s_node	*next;
}	t_node;

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

//@Leo: we need broken, and i think it should be initialized to 0
//@deniz changed broken for file_open_error
typedef struct s_cmddat
{
	char		**full_command;
	char		*full_path;
	int			infile;
	int			outfile;
	t_prompt	*prompt;
	int			file_open_error;
}	t_cmddat;

/* struct for garbage collector */
typedef struct s_grbg
{
	void	*ptr;
	struct s_grbg	*next;
}	t_grbg;

/* debug utils*/
void print_char_array(const char arr[]);
void print_str_array(char **arr);
void print_command_list(t_node *head);
void print_cmd_list(const t_node *head);
void print_cmddat(const t_cmddat *cmd);

/* exit_minishell*/
void	free_char_array(char **array);
void	free_node_list(t_node *head);
void	free_all(t_prompt	*prompt);
void	exit_ms(int exitstatus, t_prompt *prompt);
void	clear_cmmdat_lst(void *content);

/*	main	*/
void	launch_minishell(t_prompt *prompt);
void	pipe_infile_outfile(t_node *cmd_lst);

/*	init	*/
void	init_prompt_struct(t_prompt *prompt, char **envp);
int	init_env(t_prompt *prompt, char **env);
t_cmddat	*init_struct_cmd(t_prompt *prompt);

/*	signal_handler	*/
void	sigint_handler(int signum);
void	handle_sig_quit(int n);
void	signals_interactive(void);
void	handle_sig_int(int n);
void	signals_non_interactive(void);

/*	utils.c	*/
size_t	get_len_arr(char **array);
//int	ft_strcmp(const char *s1, const char *s2);
void	print_err_msg(char *cmd, char *msg);
int print_err_msg_lng(char *cmd, char *msg, char *arg);
int	ft_isspace(int c);
char	**del_str_from_array(char **array, int pos, int count);
char	**add_str_to_arr(t_prompt *prompt, char **arr, char *str);

/*	builtins.c	*/
int	get_builtin_nbr(t_cmddat *cmd);
int	execute_builtin(t_cmddat *cmd, int n, int forked);

/*	cstm_echo.c	*/
int	cstm_echo(t_cmddat *cmd_data);

/*	cstm_pwd.c	*/
int	cstm_pwd(t_cmddat *cmd_data);

/*	cstm_env.c	*/
int	cstm_env(t_cmddat *cmd_data);

/*	cstm_exit	*/
int	cstm_exit(t_cmddat *cmd_data);
int	is_only_digits(char *s);

/*	cstm_unset	*/
int	cstm_unset(t_cmddat *cmd_data);
size_t get_len_env(const char *s);

/*	cstm_cd	*/
int cstm_cd(t_cmddat *cmd_data);
int	go_home_dir(t_prompt *prompt);
int go_back_dir(t_prompt *prompt);
void modify_envp(t_prompt *prompt, char *name, char *insert);
char *get_envp(t_prompt *prompt, char *name);

/*	cstm_export.c	*/
int	cstm_export(t_cmddat *cmd);
int	print_export(t_cmddat *cmd);
void	print_line_export(t_cmddat *cmd, int i);
int	get_len_id(t_prompt *prompt, char *str, int msg);
int scan_envp(t_cmddat *cmd, char *str, int id_len);
char	*add_to_str(t_prompt *prompt, char **str, char *add);

/*	exec.c	*/
int	execute_cmds(t_prompt *prompt);
void	cls_fds(void *content);
void	run_cmd(void *content);
void	wait_update_exitstatus(t_prompt *prompt);
int	is_executable(t_cmddat *cmd_data);

/*	lexer.c*/
void	lexer(t_prompt *prompt);

/* split*/
char	**split_input(char *str, t_prompt *prompt);
char	**ft_split(char const *s, char c);
char *add_space(t_prompt *prompt, char *str);

/*	parser*/
//void	parser(t_prompt *prompt);
void	parser(t_prompt *prompt, int i, int j);
char	**fill_arr(t_prompt *main_prompt, char **prompt, int i, int len);
void	add_last_cmd_to_envp(t_prompt *prompt);

/* list_utils */
void	add_node_to_list(t_prompt *prompt, t_node **head, t_cmddat *data);
int	ft_listsize(t_node *lst);


/* envp_utils.c*/
char	*get_path_cmds(t_cmddat *cmd, char **ev);
char	*get_path(char *cmd, char **ev);
void	free_split(char **strs);


/* expander.c */
char	**expander(t_prompt *prompt, char **str, char **ev);
/*expand_var_utils.c */

char	*create_sub_var(char *str, size_t i, char **ev, ssize_t len );
ssize_t	get_len_var(char *str, int i);
char	*create_sub(char *str, size_t i, char *nb, ssize_t len );
//static char *get_substr_var(char *str, int len, char **env);
char *expand_var(t_prompt *prompt, char *str, char **ev);

/* handle_redirections.c */

int	get_type(char *str);
void	handle_redir(t_prompt *ptr);
int open_file(char **cmds, int i, int *save_fd, int io_flags[2]);
int	get_flags(int type, int file_access_type);
int	open_fd_redir(t_prompt *prompt, t_cmddat *cmd_struct, int i, int type);

int	syntax_error(t_prompt *prompt, char *token);
//t_node	fill_redir(t_node *current, int type, int i);
//char	*get_infile(t_node *current, int i);

/* quotes_utils.c */
void	get_rid_quotes(t_prompt	*prompt);
char	*get_trimmed(t_prompt *prompt, char const *s1, int squote, int dquote);
//char	*get_trimmed(char *str, int squote, int dquote);
int	malloc_len(char const *str);

/*	list_functions.c */
void	cstm_lstiter(t_node *lst, void (*f)(void *));
t_node	*cstm_lstlast(t_node *lst);
int	cstm_lstsize(t_node*lst);
void	cstm_lstclear(t_node **lst, void (*del)(void *));
void	cstm_lstdelone(t_node *lst, void (*del)(void *));


/* here_doc */
void	launch_heredoc(t_prompt *prompt, t_cmddat *cmd, int i);
int	get_heredoc(t_prompt *prompt, char *lim);
int	pipe_heredoc(char *content);

/*	garbage_collector	*/
void	*get_grbg(t_prompt *prompt, size_t nmemb, size_t size);
void	collect_grbg(t_prompt *prompt, void *new);
void	free_grbg(t_grbg *head);

/*	garbage_lib	*/
char	*grbg_strdup(t_prompt *prompt, const char *s);
char	*grbg_substr(t_prompt *prompt, char const *s, unsigned int start, size_t len);
char	*grbg_itoa(t_prompt *prompt, int n);
char	*grbg_strjoin(t_prompt *prompt, char const *s1, char const *s2);


void	signals_here_doc(void);
void	sig_handler_here_doc(int num);
// void	sig_handler_after_rl(int num);
// void	sig_handler_rl(int num);
#endif
