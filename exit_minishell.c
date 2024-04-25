/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:19:36 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/25 16:12:24 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*free and exit*/
void	exit_ms(int g_exitstatus, t_prompt *prompt)
{
	free_all(prompt);
	exit(g_exitstatus);
}

void	free_all(t_prompt *prompt)
{
	free_grbg(prompt->grbg_lst);
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
	if (cmd_struct->full_cmd)
		free_char_array(cmd_struct->full_cmd);
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
			if (temp->data->full_cmd)
				free(temp->data->full_cmd);
			if (temp->data->full_path)
				free(temp->data->full_path);
			free(temp->data);
		}
		free(temp);
	}
}

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
			free(array[i++]);
		free(array[i]);
	}
	free(array);
	return ;
}
