/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:37:35 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/01 14:06:24 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*cat < input.txt | grep "pattern" >> output.txt*/

/*
  Determines the type of redirection for the given string `str`
  and returns the corresponding type value.

  Parameters:
    - str: Pointer to the string representing a command or redirection.

  Returns:
    - 1 if the redirection is an infile-redirection ('<').
    - 2 if the redirection is a here_doc-redirection ('<<').
    - 3 if the redirection is a write to outfile ('>').
    - 4 if the redirection is an append to outfile ('>>').
    - 0 if no redirection type is detected.
*/

int	get_type(char *str)
{
	int	type;
	int	i;

	i = 0;
	type = 0;
	if (ft_strlen(str) == 1 && str[i] == '<' )
		type = 1;
	if (type == 1 && str[i + 1] && str[i + 1] == '<')
	{
		type = 2;
		printf("here_doc-redirection\n");
	}
	if (type == 0 && str[i] == '>')
	{
		type = 3;
		printf("write to outfile\n");
	}
	if (type == 3 && str[i + 1] && str[i + 1] == '>')
		{
			type = 4;
			printf("append to outfile\n");
		}
	return (type);
}

/*
  Handles redirections within the commands stored in the prompt structure `ptr`.
  It iterates through the command list and processes each command to identify and handle redirections.

  Parameters:
    - ptr: Pointer to the prompt structure containing the command list.

  Returns: None
*/
void	handle_redir(t_prompt *ptr)
{
	int i;
	int type;
	t_node *current_node;
	t_cmddat *cmd_data;

	current_node = ptr->cmd_list;
	while (current_node != NULL)
	{
		cmd_data = current_node->data;
		if (cmd_data)
		{
			i = 0;
			while (cmd_data->full_command[i])
			{
				type = get_type(cmd_data->full_command[i]);
				//printf("i : %i -- %s %s\n", i,cmd_data->full_command[i], cmd_data->full_command[i+1]);
				//print_str_array(cmd_data->full_command);
				if (type < 5 && type > 0)
				{
					open_fd_redir(ptr, cmd_data, i, type);
					// printf("avant : ");
					// print_str_array(cmd_data->full_command);
					cmd_data->full_command = del_str_from_array(cmd_data->full_command, i, 2);
					// printf("apres : ");
					// print_str_array(cmd_data->full_command);
					i -= 1;
				}
				i++;
			}
		}
		current_node = current_node->next;
	}
}

/*
if save_fd > 1 , it means that it's already open and we need to close it
*/

int open_file(char **cmds, int i, int *save_fd, int i_flags, int o_flags )
{
	printf("enters open_file\n");
	if (*save_fd > 1)
	{
		if (close(*save_fd) == -1)
			printf("Error while attempting to close a file");
	}
	if (cmds[i + 1] && cmds[i + 1][0] != '>' && cmds[i + 1][0] != '<')
	{
		if (o_flags != 0)
			*save_fd = open(cmds[i + 1], i_flags, o_flags);
		else
			*save_fd = open(cmds[i + 1], i_flags);
		if (*save_fd == -1)
		{
			printf("%s No such file or directory\n", cmds[i + 1]);
			return (1);
		}
	}
	return (0);
}

/*
Indicates that the file should be...
O_RDONLY: opened in read-only mode.
O_WRONLY: opened in write-only mode.
O_CREAT: created if it does not exist.
O_TRUNC: truncated (emptied) if it already exists.
O_APPEND: Indicates that data should be appended to the
 end of the file during writing.
00644: octal value used to specify the file permissions when creating it.
In this case, 00644 grants read and write permissions to
the file owner, and read permissions to other users.
*/

int	get_flags(int type, int file_access_type)
{
	if (file_access_type == 0)
	{
		if (type == 1 || type == 2)
			return (O_RDONLY);
		if (type == 3)
			return (O_WRONLY | O_CREAT | O_TRUNC);
		if (type == 4)
			return (O_WRONLY | O_CREAT | O_APPEND);
	}
	else if (file_access_type == 1)
	{
		if (type == 1 || type == 2)
			return (0);
		if (type == 3 || type == 4)
			return (00644);
	}
	return (0);
}


int	open_fd_redir(t_prompt *prompt, t_cmddat *cmd_struct, int i, int type)
{
	int	input_flags;
	int	output_flags;

	input_flags = get_flags(type, 0);
	output_flags = get_flags(type, 1);
	if (type == 1)
		cmd_struct->file_open_error = open_file(cmd_struct->full_command, i, &cmd_struct->infile, input_flags, output_flags);
	else if (type == 2)
		printf("to do : start here_doc\n ");
	else if (type == 3)
		cmd_struct->file_open_error = open_file(cmd_struct->full_command, i, &cmd_struct->outfile, input_flags, output_flags);
	else
		cmd_struct->file_open_error = open_file(cmd_struct->full_command, i + 1, &cmd_struct->outfile, input_flags, output_flags);
	return 0;
}



