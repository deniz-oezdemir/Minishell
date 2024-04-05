/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:08:23 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/05 13:34:56 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cstm_lstiter(t_node *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->data); //data is of type cmd_dat
		lst = lst->next;
	}
}

t_node	*cstm_lstlast(t_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	cstm_lstsize(t_node*lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	cstm_lstclear(t_node **lst, void (*del)(void *))
{
	t_node	*next;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		del((*lst)->data);
		free(*lst);
		*lst = next;
	}
}
