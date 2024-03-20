/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:41 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/20 20:29:08 by ecarlier         ###   ########.fr       */
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
	return (ptr);
}

void	parser(t_prompt *prompt)
{
	t_cmddat	*ptr;
	int	i;
	int count;

	count = 1;
	i = 0;

	while (prompt->commands[i])
	{
		print_char_array(prompt->commands[i]);
		if (i == 0 || prompt->commands[i][0] == '|')
		{
			// printf("New node\n");
			// if (i != 0)
				// count = 0;
			ptr = init_struct_cmd();
			if (!ptr)
				return ;
			add_node_to_list(&(prompt->cmd_list), ptr);
		}
		else
		{
			count++;
		}

			//printf("Count %d\n", count);
		i++;
	}
	printf("Taille de cmd_list : %d\n", ft_listsize(prompt->cmd_list));
	print_command_list(prompt->cmd_list);
}



// t_cmddat	fill_cmd(t_cmddat *ptr, int count, char **arr, int i)
// {


// }
// #define MAX_COMMANDS 1000

// void	parser(t_prompt *prompt)
// {
// 	t_cmddat	*ptr;
// 	int	j;
// 	int	i;
// 	int count;
// 	char *cmd_seq[MAX_COMMANDS];

// 	ft_memset(cmd_seq, 0, sizeof(cmd_seq));
// 	//count = 1;
// 	i = 0;

// 	while (prompt->commands[i])
// 	{
// 		print_char_array(prompt->commands[i]);
// 		if (i == 0 || prompt->commands[i][0] == '|')
// 		{
// 			// printf("New node\n");
// 			// if (i != 0)
// 				// count = 0;
// 			ptr = init_struct_cmd();
// 			if (!ptr)
// 				return ;
// 			j = 0;
// 			while (j < i)
// 			{
// 				ptr->full_command[j] = ft_strdup(cmd_seq[j]);
// 				j++;
// 			}
// 			ptr->full_command[j] = NULL;
// 			add_node_to_list(&(prompt->cmd_list), ptr);
// 			ft_memset(cmd_seq, 0, sizeof(cmd_seq));
// 		}
// 		else
// 			cmd_seq[i] = ft_strdup(prompt->commands[i]);
// 			// count++;
// 			//printf("Count %d\n", count);
// 		i++;

// 	}
// 	if (ptr)
// 	{
// 		j = 0;
// 		while (j < i)
// 		{
// 			ptr->full_command[j] = ft_strdup(cmd_seq[j]);
// 			j++;
// 		}
// 		ptr->full_command[j] = NULL;
// 	}
// 	printf("Taille de cmd_list : %d\n", ft_listsize(prompt->cmd_list));
// 	print_command_list(prompt->cmd_list);
// }


