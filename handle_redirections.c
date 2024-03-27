/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:37:35 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/27 15:37:00 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*cat < input.txt | grep "pattern" >> output.txt*/


int	get_type(char *str)
{
	int	type;
	int	i;

	i = 0;

	//printf("str = %s\n", str);
	type = 0;
	if (ft_strlen(str) == 1 && str[i] == '<' )
	{
		type = 1;
		printf("infile-redirection\n");
	}
	if (type == 1 && str[i + 1] && str[i + 1] == '<')
	{
		type = 2;
		printf("here_doc-redirection\n");
	}
	if (type == 0 &&  str[i] == '>')
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

void	handle_redir(t_prompt *ptr)
{

	int i;
	t_node *current_node;
	t_cmddat *cmd_data;

	current_node = ptr->cmd_list;
	while (current_node != NULL)
	{
		cmd_data = current_node->data;
		if (cmd_data)
		{
			i = 0;
			while(cmd_data->full_command[i])
			{
				get_type(cmd_data->full_command[i]);

				i++;
			}
		}
		current_node = current_node->next;
	}

}
