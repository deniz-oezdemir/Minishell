/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:41 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/27 17:44:26 by ecarlier         ###   ########.fr       */
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


static t_cmddat	*init_struct_cmd(void)
{
	t_cmddat	*ptr;

	ptr = malloc(sizeof(t_cmddat));
	if (!ptr)
		return (NULL);
	ptr->full_command = NULL;
	ptr->full_path = NULL;
	ptr->infile = STDIN_FILENO;
	ptr->outfile = STDOUT_FILENO;
	//printf("New_node created\n");
	return (ptr);
}

char	**fill_arr(char **prompt, int i, int len)
{
	char **temp;
	int j;
	j = 0;

	temp = malloc((sizeof(char *) * len + 1));
	if (!temp)
		return (NULL);
	while (len > 0)
	{
		temp[j] = ft_strdup(prompt[i]);
		i++;
		j++;
		len--;
	}
	temp[j] = NULL;
	//print_str_array(ptr->full_command);
	return (temp);
}

/*
Before :
After :
 */
void	parser(t_prompt *prompt)
{
	t_cmddat	*ptr;
	char **temp;
	int	i;
	int	j;
	j = 1;
	i = 0;

	//get_type(prompt);

	while (prompt->commands[i])
	{
		if (i == 0 || prompt->commands[i][0] == '|' && prompt->commands[i+1] && prompt->commands[i][0])
		{
			ptr = init_struct_cmd();
 			if (!ptr)
				return ;
 			add_node_to_list(&(prompt->cmd_list), ptr);
			if (i != 0)
			{
				ptr->full_command = fill_arr(prompt->commands, i - j, j);
				ptr->full_path = get_path_cmds(ptr, prompt->envp);
				prompt->cmd_list->data->full_command = fill_arr(prompt->commands, i - j, j);
				j = 0;
			}
		}
		else
			j++;
		i++;
	}
	if (ptr)
		ptr->full_command = fill_arr(prompt->commands, i - j, j);
		ptr->full_path = get_path_cmds(ptr, prompt->envp);


	handle_redir(prompt);
	print_cmd_list(prompt->cmd_list);
}

