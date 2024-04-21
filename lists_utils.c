/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:15:48 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/21 23:22:53 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_node_to_list(t_prompt *prompt, t_node **head, t_cmddat *data)
{
    t_node *new_node;
    t_node *current;

    new_node = get_grbg(prompt, 1, sizeof(t_node));
    if (!new_node)
        return ;
    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}


// void	add_node_to_list(t_node **head, t_cmddat *data)
// {
// 	t_node	*new_node;
// 	t_node	*current;

// 	new_node = malloc(sizeof(t_node));
// 	if (!new_node)
// 		return ;
// 	new_node->data = data;
// 	new_node->next = NULL;
// 	if (*head == NULL)
// 	{
// 		*head = new_node;
// 	}
// 	else
// 	{
// 		current = *head;
// 		while (current->next != NULL)
// 		{
// 			current = current->next;
// 		}
// 		current->next = new_node;
// 	}
// }

int	ft_listsize(t_node *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
// void	ft_lstadd_back(t_list **lst, t_list *newnode)
// {
// 	t_list	*start;

// 	start = *lst;
// 	if (*lst)
// 	{
// 		while (start->next)
// 			start = start->next;
// 		start->next = newnode;
// 	}
// 	else
// 		*lst = newnode;
// }


// void	ft_lstadd_front(t_list **lst, t_list *newnode)
// {
// 	newnode->next = *lst;
// 	*lst = newnode;
// }

// void	ft_lstclear(t_list **lst, void (*del)(void*))
// {
// 	t_list	*start;
// 	t_list	*temp;

// 	if (!lst)
// 		return ;
// 	start = *lst;
// 	temp = NULL;
// 	while (start)
// 	{
// 		temp = start;
// 		start = start->next;
// 		del(temp->content);
// 		free(temp);
// 	}
// 	*lst = NULL;
// }
