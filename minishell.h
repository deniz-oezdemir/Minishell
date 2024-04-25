/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:26:53 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/25 16:23:51 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int				g_exitstatus;

typedef struct s_node	t_node;
typedef struct s_prompt	t_prompt;
typedef struct s_cmddat	t_cmddat;
typedef struct s_grbg	t_grbg;

typedef struct s_prompt
{
	char				*input_string;
	char				**commands;
	t_node				*cmd_list;
	char				**envp;
	pid_t				pid;
	int					stop;
	t_grbg				*grbg_lst;
}						t_prompt;

typedef struct s_node
{
	t_cmddat			*data;
	struct s_node		*next;
}						t_node;

typedef struct s_cmddat
{
	char				**full_cmd;
	char				*full_path;
	int					infile;
	int					outfile;
	t_prompt			*prompt;
	int					file_open;
}						t_cmddat;

typedef struct s_grbg
{
	void				*ptr;
	struct s_grbg		*next;
}						t_grbg;

/* debug utils*/
/*NEED TO DELETE THIS*/
void					print_char_array(const char arr[]);
void					print_str_array(char **arr);
void					print_command_list(t_node *head);
void					print_cmd_list(const t_node *head);
void					print_cmddat(const t_cmddat *cmd);

/* exit_minishell*/
void					free_char_array(char **array);
void					free_node_list(t_node *head);
void					free_all(t_prompt *prompt);
void					exit_ms(int g_exitstatus, t_prompt *prompt);
void					clear_cmmdat_lst(void *content);

/*	main	*/
void					launch_minishell(t_prompt *prompt);
void					pipe_infile_outfile(t_node *cmd_lst);

/*	init	*/
void					init_prompt_struct(t_prompt *prompt, char **envp);
int						init_env(t_prompt *prompt, char **env);
t_cmddat				*init_struct_cmd(t_prompt *prompt);

/*	lexer.c*/
void					lexer(t_prompt *prompt);

char					**split_input(char *str, t_prompt *prompt);
char					**ft_split(char const *s, char c);
char					*handle_spaces(t_prompt *prompt, char *str, size_t i,
							int j);
char					**ft_create_substrs(t_prompt *p, char **aux,
							char const *s, char *set);

/* quotes_utils.c */
void					get_rid_quotes(t_prompt *prompt);
char					*get_trimmed(t_prompt *prompt, char const *s1,
							int squote, int dquote);
int						malloc_len(char const *str);

/*	parser*/
void					parser(t_prompt *prompt, int i, int j);
char					**fill_arr(t_prompt *main_prompt, char **prompt, int i,
							int len);
void					add_last_cmd_to_envp(t_prompt *p);
int						check_double_pipes(t_prompt *prompt);

/* handle_redirections.c */
int						get_type(char *str);
void					handle_redir(t_prompt *ptr, int type);
int						open_file(char **cmds, int i, int *save_fd,
							int io_flags[2]);
int						get_flags(int type, int file_access_type);
int						open_fd_redir(t_prompt *prompt, t_cmddat *cmd_struct,
							int i, int type);
int						syntax_error(t_prompt *prompt, char *token);

/* here_doc */
void					launch_heredoc(t_prompt *prompt, t_cmddat *cmd, int i);
int						get_heredoc(t_prompt *prompt, char *lim);
int						pipe_heredoc(char *content);

/*	builtins.c	*/
int						get_builtin_nbr(t_cmddat *cmd);
int						execute_builtin(t_cmddat *cmd, int n, int forked);

/*	cstm_echo.c	*/
int						cstm_echo(t_cmddat *cmd_data);

/*	cstm_pwd.c	*/
int						cstm_pwd(t_cmddat *cmd_data);

/*	cstm_env.c	*/
int						cstm_env(t_cmddat *cmd_data);

/*	cstm_exit	*/
int						cstm_exit(t_cmddat *cmd_data);
int						is_only_digits(char *s);

/*	cstm_unset	*/
int						cstm_unset(t_cmddat *cmd);
size_t					get_len_env(const char *s);

/*	cstm_cd	*/
int						cstm_cd(t_cmddat *cmd_data);
int						go_home_dir(t_prompt *prompt);
int						go_back_dir(t_prompt *prompt);
void					modify_envp(t_prompt *prompt, char *name, char *insert);
char					*get_envp(t_prompt *prompt, char *name);

/*	cstm_export.c	*/
int						cstm_export(t_cmddat *cmd);
int						print_export(t_cmddat *cmd);
void					print_line_export(t_cmddat *cmd, int i);
int						get_len_id(t_prompt *prompt, char *str, int msg);
int						scan_envp(t_cmddat *cmd, char *str, int id_len);
char					*add_to_str(t_prompt *prompt, char **str, char *add);

/*	exec.c	*/
int						execute_cmds(t_prompt *prompt);
void					cls_fds(void *content);
void					run_cmd(void *content);
void					wait_update_g_exitstatus(t_prompt *prompt);
int						is_executable(t_cmddat *cmd_data);

/*	signal_handler	*/
void					sigint_handler(int signum);
void					handle_sig_quit(int n);
void					signals_interactive(void);
void					handle_sig_int(int n);
void					signals_non_interactive(void);

/*	garbage_collector	*/
void					*get_grbg(t_prompt *prompt, size_t nmemb, size_t size);
void					collect_grbg(t_prompt *prompt, void *new);
void					free_grbg(t_grbg *head);

/*	garbage_lib	*/
char					*grbg_strdup(t_prompt *prompt, const char *s);
char					*grbg_substr(t_prompt *prompt, char const *s,
							unsigned int start, size_t len);
char					*grbg_itoa(t_prompt *prompt, int n);
char					*grbg_strjoin(t_prompt *prompt, char const *s1,
							char const *s2);

/*	list_functions.c */
void					cstm_lstiter(t_node *lst, void (*f)(void *));
t_node					*cstm_lstlast(t_node *lst);
int						cstm_lstsize(t_node *lst);
void					cstm_lstclear(t_node **lst, void (*del)(void *));
void					cstm_lstdelone(t_node *lst, void (*del)(void *));

/*	utils.c	*/
size_t					get_len_arr(char **array);
void					print_err_msg(char *cmd, char *msg);
int						print_err_msg_lng(char *cmd, char *msg, char *arg);
int						ft_isspace(int c);
char					**del_str(char **array, int pos, int count);
char					**add_str_to_arr(t_prompt *prompt, char **arr,
							char *str);

/* list_utils */
void					add_node_to_list(t_prompt *prompt, t_node **head,
							t_cmddat *data);
int						ft_listsize(t_node *lst);

/* envp_utils.c*/
char					*get_path_cmds(t_cmddat *cmd, char **ev);
char					*get_path(char *cmd, char **ev, size_t i);
void					free_split(char **strs);

/* expander.c */
char					**expander(t_prompt *prompt, char **str, char **ev);
char					*handle_g_exitstatus(t_prompt *prompt, int i, char *str,
							char *sub_str);

/*expand_var_utils.c */
char					*create_sub_var(char *str, size_t i, char **ev,
							ssize_t len);
ssize_t					get_len_var(char *str, int i);
char					*create_sub(char *str, size_t i, char *nb, ssize_t len);
char					*expand_var(t_prompt *prompt, char *str, char **ev,
							int i);
char					*handle_expansion(t_prompt *prompt, char *str, int q[4],
							char *sub_str);

#endif
