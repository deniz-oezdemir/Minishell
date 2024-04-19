/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:50:33 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/19 12:06:44 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	**head = address of head ptr of garbage list
	nmemb and size of new memory space (same as for ft_calloc) */
void	*get_grbg(t_grbg **head, size_t nmemb, size_t size)
{
	void *new;

	new = ft_calloc(nmemb, size);
	if (!new)
	{
		ft_putstr_fd("memory allocation error\n", 2);
		//set exitstatus, free stuff
		return (NULL);
	}
	//printf("allocated new: %x\n", new);
	collect_grbg(head, new);
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
	//printf("allocated node: %x\n", node);
	node->ptr = new;
	//printf("check: node->ptr: %x is equal to allocated new above?\n", node->ptr);
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

	//printf("head before free: %x\n", head);
	curr = head;
	while (curr)
	{
		if(curr->ptr)
		{
			//printf("curr->ptr before free: %x\n", curr->ptr);
			free(curr->ptr);
		}
		prev = curr;
		if (curr->next)
			curr = curr->next;
		else
		{
			//printf("curr before free: %x\n", curr);
			free(curr);
			return ;
		}
		//printf("prev=curr before free: %x\n", prev);
		free(prev);
	}
}
