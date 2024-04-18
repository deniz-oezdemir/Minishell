/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:50:33 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/18 19:04:29 by denizozd         ###   ########.fr       */
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
	node->ptr = new;
	node->next = NULL;
	printf("before *head: %x\n", (*head));
	if (!(*head)) //list is empty
	{
		*head = node;
		printf("after *head: %x\n", (*head));
		return ;
	}
	printf("after *head: %x\n", (*head));
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

	printf("before free head: %x\n", head);
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
