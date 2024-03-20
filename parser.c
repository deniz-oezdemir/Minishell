/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:41 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/20 21:15:43 by ecarlier         ###   ########.fr       */
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
	printf("New_node created\n");
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
	while(len > 0)
	{
		temp[j] = ft_strdup(prompt[i]);
		//print_char_array(prompt[i]);
		// if (!temp[j])
        // {
        //     while (j--)
        //         free(temp[j]);
        //     free(temp);
        //     return NULL;
        // }
		i++;
		j++;
		len--;
	}
	temp[j] = NULL;

	printf("temp :");
	print_str_array(temp);
	return (temp);
}


void	parser(t_prompt *prompt)
{
	//int count;
	//temp_cmds[0] = NULL;
	//count = 1;
	//t_node	*temp_cmds[2];

	t_cmddat	*ptr;
	char **temp;
	int	i;
	int	j;
	j = 1;
	i = 0;

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
				fill_arr(prompt->commands, i - j, j);
				j = 0;
			}

		}
		else
		{
			//print_char_array(prompt->commands[i]);
			j++;
			printf("Current index = %d -- indx start_comnd = %d \n", i, j);
		}

		i++;

	}
}

// void	parser(t_prompt *prompt)
// {
// 	t_cmddat	*ptr;
// 	int	i;
// 	int count;

// 	count = 1;
// 	i = 0;

// 	while (prompt->commands[i])
// 	{
// 		print_char_array(prompt->commands[i]);
// 		if (i == 0 || prompt->commands[i][0] == '|')
// 		{
// 			printf("New node\n");
// 			if (i != 0)
// 			{
// 				//fill_command(ptr, count, prompt->commands, i);
// 				count = 0;
// 			}
// 			ptr = init_struct_cmd();
// 			if (!ptr)
// 				return ;
// 			add_node_to_list(&(prompt->cmd_list), ptr);
// 		}
// 		else
// 		{
// 			count++;
// 			printf("Count %d\n", count);
// 		}
// 		i++;
// 		printf("Taille de cmd_list : %d", ft_listsize(prompt->cmd_list));
// 	}
// }


