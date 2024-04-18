/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:50:33 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/18 17:53:07 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	*head = address of head of garbage list
	nmemb and size of new memory space (same as for ft_calloc) */
void	*get_grbg(t_grbg *head, size_t nmemb, size_t size)
{
	void *new;

	new = ft_calloc(nmemb, size);
	if (!new)
	{
		ft_putstr_fd("memory allocation error\n", 2);
		//set exitstatus, free stuff
		return ;
	}
	collect_grbg(&head, new);
	return (new);
}


void	collect_grbg(t_grbg **head, void *new)
{
	t_grbg *node;
	t_grbg *tmp;

	node = ft_calloc(1, sizeof(t_grbg));
	if (!node)
	{
		ft_putstr_fd("memory allocation error\n", 2);
		//set exitstatus, free stuff, exit
		return ;
	}
	node->ptr = new;
	node->next = NULL;
	if (!(*head)) //list is empty
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next) //list is not empty
		tmp = tmp->next; //go to last node
	tmp->next = node; //add new at end
	return ;
}

void	free_grbg(t_grbg *head)
{
	t_grbg *curr;
	t_grbg *prev;

	curr = head;
	while (curr)
	{
		if(curr->ptr)
			free(curr->ptr);
		prev = curr;
		if (curr->next)
			curr = curr->next;
		else
		{
			free(curr);
			return ;
		}
		free(prev);
	}
}
