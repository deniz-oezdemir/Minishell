/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:19:36 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/14 20:05:20 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*free and exit*/
void	exit_ms(int exitstatus, t_prompt *prompt)
{
	free_all(prompt);
	exit(exitstatus);
}

void	free_all(t_prompt	*prompt)
{
	if (prompt->input_string)
		free(prompt->input_string);
	if (prompt->commands)
		free_char_array(prompt->commands);
	if (prompt->envp)
		free_char_array(prompt->envp);
	free_node_list(prompt->cmd_list);
	rl_clear_history();
	if (prompt)
		free(prompt);
}

void	clear_cmmdat_lst(void *content)
{
	t_cmddat	*cmd_struct;

	cmd_struct = (t_cmddat *)content;
	if (cmd_struct->full_path)
		free(cmd_struct->full_path);
	if (cmd_struct->full_command)
		free_char_array(cmd_struct->full_command);
	free(cmd_struct);
}


void	free_node_list(t_node *head)
{
	t_node	*current;
	t_node	*temp;

	current = head;
	while (current)
	{
		temp = current;
		current = current->next;
		if (temp && temp->data)
		{
			if (temp->data->full_command)
				free(temp->data->full_command);
			if (temp->data->full_path)
				free(temp->data->full_path);
			free(temp->data);
		}
		free(temp);
	}
}


void	free_char_array(char **array)
{
	//@Leo: below fixed the leak in ft_calloc when ctrl+d and another one when exit
	int	i;

	i = 0;
	if (array)
	{
		while(array[i])
			free(array[i++]);
		free(array[i]);
	}
	free(array);
	return ;


	/* @Leo: delete below whenever you do need it anymore as reference
	if (array == NULL)
		return ;
	while (*array != NULL)
	{
		free(*array);
		array++;
	}
	//free(array);*/
}
