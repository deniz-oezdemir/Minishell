/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:19:36 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/25 16:30:14 by ecarlier         ###   ########.fr       */
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

