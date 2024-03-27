/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:37:35 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/27 18:14:20 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*cat < input.txt | grep "pattern" >> output.txt*/

/*
1 = infile-redirection
2 = here_doc-redirection
3 = write to outfile
4 = append to outfile
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
		//printf("here_doc-redirection\n");
	}
	if (type == 0 &&  str[i] == '>')
	{
		type = 3;
		//printf("write to outfile\n");
	}
	if (type == 3 && str[i + 1] && str[i + 1] == '>')
		{
			type = 4;
			printf("append to outfile\n");
		}
	return (type);
}

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
				if (type >= 1 && type <= 4)
						fill_redir(current_node , type, i);
				i++;
			}
		}
		current_node = current_node->next;
	}

}

/*
current :
type : between 1 and 4
i : points to the redirection token (<, >, <<, >>)
*/
t_node	fill_redir(t_node *current, int type, int i)
{
	char *infile;
	char *outfile;

	if (type == 1)
	{
		infile = get_infile(current, i);
		printf("infile : %s\n", infile);
	}
	// else if (type == 2)
	// 	printf("start here_doc\n");
	// else if (type == 3)
	// {

	// }
	// else if (type == 3)
	// {

	// }
	// else if (type == 4)
	// {

	// }

	//current->data->infile = infile;

	//free
	return (*current);
}


char	*get_infile(t_node *current, int i)
{
	char	*infile;

	if (current->data->full_command[i + 1])
	{
		infile = ft_strdup(current->data->full_command[i + 1]);
	}
	else
	{
		printf("syntax error near unexpected token `newline'\n");
	}
	return (infile);

}
