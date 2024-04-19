/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:41 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/19 17:04:15 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Iterate over the two-dimensional array
Whenever a redirection is found, check the type of redirection and retrieve a file descriptor containing the info we need as the infile
Check that the file descriptor that has been opened is valid (!= -1) and continue
If a pipe is found, add a new node to the list of commands
In all other cases add whatever words are found to the argument list (argv) we call full_cmd
*/

/*
prompt->commands
["ls", "-l", "|", "grep", "'file.txt'", ]
*/


/*
  Initializes a new structure t_cmddat with default values.
  Allocates memory for the structure and returns a pointer to it.

  Returns:
    - Pointer to the newly initialized t_cmddat structure.
*/
static t_cmddat	*init_struct_cmd(t_prompt *prompt)
{
	t_cmddat	*ptr;

	ptr = get_grbg(1, sizeof(t_cmddat));
	if (!ptr)
		return (NULL);
	ptr->full_command = NULL;
	ptr->full_path = NULL;
	ptr->infile = STDIN_FILENO;
	ptr->outfile = STDOUT_FILENO;
	ptr->prompt = prompt;
	ptr->file_open_error = 0;
	return (ptr);
}

/*
  Creates and fills a new array of strings from the `prompt` array.
  It starts filling from index `i` and fills `len` number of elements.
  Memory is dynamically allocated for the new array.

  Parameters:
    - prompt: Pointer to the original array of strings.
    - i:      Starting index to begin filling from.
    - len:    Number of elements to fill in the new array.

  Returns:
    - Pointer to the newly created array of strings.
*/

//main_prompt can be removed as prompt is global variable now
char	**fill_arr(t_prompt *main_prompt, char **prompt, int i, int len)
{
	char **temp;
	int j;
	j = 0;

	temp = NULL;
	//print_str_array(prompt);
	//temp = malloc(sizeof(char *) * (len + 1));
	temp = get_grbg(len + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	while (len > 0)
	{
		//temp[j] = ft_strdup(prompt[i]);
		temp[j] = grbg_strdup(prompt[i]);
		i++;
		j++;
		len--;
	}
	temp[j] = NULL;

	//print_str_array(ptr->full_command);
	return (temp);
}

/*
  Parses the input commands stored in the prompt structure.
  It constructs a list of commands with their arguments and other details.
  Also handles redirections and pipes.

  Parameters:
    - prompt: Pointer to the prompt structure containing input commands.
*/
/*
check if the last char is | < > */
static void	check_last_char(t_prompt *prompt)
{
	int	len_ar;
	char last_char;


	len_ar = get_len_arr(prompt->commands) - 1;
	if (len_ar < 0 || prompt->commands[len_ar] == NULL || prompt->commands[len_ar][0] == '\0')
		return;

	last_char = prompt->commands[len_ar][0] ;

	if (last_char == '|' || last_char == '<' || last_char == '>' )
	{
		prompt->stop = 1;
		syntax_error(prompt, prompt->commands[len_ar]);
	}
}
/*
check pour chaque struct si le dernier char est < ou > */
static void	check_token(t_prompt *prompt)
{
	t_node *current_node;
	t_cmddat *cmd_data;
	int	len_arr;
	char	last_char;

	current_node = prompt->cmd_list;
	while (current_node != NULL)
	{
		cmd_data = current_node->data;
		len_arr = get_len_arr(cmd_data->full_command) - 1 ;
		last_char = cmd_data->full_command[len_arr][0];
		if (last_char == '|' || last_char == '<' || last_char == '>' )
		{
			prompt->stop = 1;
			syntax_error(prompt, cmd_data->full_command[len_arr]);
			free_node_list(prompt->cmd_list);
			prompt->cmd_list = NULL;
			break;
		}
		current_node = current_node->next;
	}
}


void	parser(t_prompt *prompt)
{
	t_cmddat	*ptr;
	int			i;
	int			j;

	j = 0;
	i = 0;

	ptr = NULL;
	get_rid_quotes(prompt);
	check_last_char(prompt);
	while (prompt && prompt->commands && prompt->commands[i] != NULL && prompt->stop == 0)
	{
		ptr = init_struct_cmd(prompt);
		if (!ptr)
			return ;
		add_node_to_list(&(prompt->cmd_list), ptr);
		while (prompt->commands[i] != NULL && prompt->commands[i][0] != '|')
		{
			i++;
			j++;
		}
		ptr->full_command = fill_arr(prompt, prompt->commands, i - j, j);
		ptr->full_path = get_path_cmds(ptr, prompt->envp); //@Deniz: not gc'ed within get_path_cmds
		collect_grbg(ptr->full_path);
		if (prompt->commands[i] == NULL)
			break;
		i++;
		j = 0;
	}
	//print_cmd_list(prompt->cmd_list);
	check_token(prompt); //@Leo: what does this do - it frees a lot of things but it's hard for me to judge whether thats necessary with the gc - left it as is for now
	if (prompt->stop == 0)
		handle_redir(prompt);
	add_last_cmd_to_envp(prompt);
}

// void	parser(t_prompt *prompt)
// {
// 	t_cmddat	*ptr;
// 	char **temp;
// 	int	i;
// 	int	j;
// 	j = 1;
// 	i = 0;

// 	ptr = NULL;
// 	temp = NULL;
// 	get_rid_quotes(prompt);
// 	check_last_char(prompt);

// 	while (prompt && prompt->commands && prompt->commands[i] && prompt->stop == 0)
// 	{
// 		if (i == 0 || prompt->commands[i][0] == '|' && prompt->commands[i + 1] && prompt->commands[i][0])
// 		{

// 			ptr = init_struct_cmd(prompt);
//  			if (!ptr)
// 				return ;
//  			add_node_to_list(&(prompt->cmd_list), ptr);
// 			if (i != 0)
// 			{
// 				printf("%d \n\n", i);
// 				ptr->full_command = fill_arr(prompt->commands, i - j, j);
// 				prompt->cmd_list->data->full_path = get_path_cmds(ptr, prompt->envp);
// 				prompt->cmd_list->data->full_command = fill_arr(prompt->commands, i - j, j);
// 				j = 0;
// 			}
// 		}
// 		else
// 			j++;
// 		i++;
// 	}
// 	if (ptr && prompt->stop == 0)
// 	{

// 		ptr->full_command = fill_arr(prompt->commands, i - j, j);
// 		ptr->full_path = get_path_cmds(ptr, prompt->envp);
// 	}
// 	check_token(prompt);

// 	if (prompt->stop == 0)
// 	{
// 		handle_redir(prompt);
// 		print_cmd_list(prompt->cmd_list);
// 	}

// 	add_last_cmd_to_envp(prompt);
// }

void	add_last_cmd_to_envp(t_prompt *prompt)
{
	int	l;

	l = 0;
	if (!prompt->cmd_list->data->full_command)
		return ;
	l = get_len_arr(prompt->cmd_list->data->full_command);
	if (l)
		modify_envp(prompt, "_", grbg_strdup(prompt->cmd_list->data->full_command[l - 1]), 0);
}


