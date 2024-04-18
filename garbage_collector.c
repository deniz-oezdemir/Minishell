#include "minishell.h"

//List that stores pointers to malloced memory that should be freed
//	either between every loop,
//	or only at the exit of program.

//Function that
//	malloc/ft_callocs
//	adds the pointer to above list
//	returns the pointer

//Function that frees depending on flag
//	every loop
//	only at exit


//flg 1 for at every loop, 2 for at exit
typedef struct s_grbg
{
	void	*ptr;
	int		flg;
	struct s_grbg	*next;
}	t_grbg;

/*	**head = address of garbage list head
	nmemb and size of new memory space (same as for ft_calloc)
	f = 1 for every loop or 2 only at exit freeing	*/
void	*get_grbg(t_grbg *head, size_t nmemb, size_t size, int f)
{
	void *new;

	new = ft_calloc(nmemb, size);
	if (!new)
	{
		ft_putstr_fd("memory allocation error\n", 2);
		//set exitstatus, free stuff
		return ;
	}
	collect_grbg(head, new, f);//@Deniz: initialize all to 0
	return (new);
}

void collect_grbg(t_grbg *head, void *new, int f)
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
	node->flg = f;
	node->next = NULL;
	if (!head) //list is empty
	{
		head = node;
		return ;
	}
	while (head->next)
		head = head->next; //head is last
	head->next = node;
	return ;
}

void free_grbg(t_grbg *head, int f)
{
	while (head)
	{
		if(head->ptr && head->flg == f)
			free(head->ptr);
		if (head->next)
			head = head->next;
	}
}
