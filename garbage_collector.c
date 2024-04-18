#include "minishell.h"

//List that stores pointers to malloced memory that should be freed

//Function that
//	malloc/ft_callocs
//	adds the pointer to above list
//	returns the pointer


typedef struct s_grbg
{
	void	*ptr;
	struct s_grbg	*next;
}	t_grbg;

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
	collect_grbg(head, new);
	return (new);
}

void collect_grbg(t_grbg *head, void *new)
{
	t_grbg *node;

	node = ft_calloc(1, sizeof(t_grbg));
	if (!node)
	{
		ft_putstr_fd("memory allocation error\n", 2);
		//set exitstatus, free stuff, exit
		return ;
	}
	node->ptr = new;
	node->next = NULL;
	if (!head) //list is empty
	{
		head = node;
		return ;
	}
	while (head->next) //list is not empty
		head = head->next; //go to last node
	head->next = node; //add new at end
	return ;
}

void free_grbg(t_grbg *head)
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
