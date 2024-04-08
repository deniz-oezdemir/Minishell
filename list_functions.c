/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:08:23 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/08 10:15:33 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cstm_lstiter(t_node *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
		printf("c3.1\n");
	while (lst)
	{
		printf("c3.2\n");
		f(lst->data); //data is of type cmd_dat
		printf("c3.3\n");
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
