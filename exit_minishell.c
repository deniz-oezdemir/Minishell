/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:19:36 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/05 14:52:52 by ecarlier         ###   ########.fr       */
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

void	free_node_list(t_node *head)
{
	t_node	*current;
	t_node	*temp;

	current = head;
	while (current)
	{
		temp = current;
		current = current->next;
		if (temp->data)
		{
			free(temp->data->full_command);
			free(temp->data->full_path);
			free(temp->data);
		}
		free(temp);
	}
}

void	free_char_array(char **array)
{
	if (array == NULL)
		return ;
	while (*array != NULL)
	{
		free(*array);
		array++;
	}
	//free(array);
}
