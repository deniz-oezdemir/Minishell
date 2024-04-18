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
	free = 1 for every loop or 2 only at exit freeing	*/
void	*add_grbg(t_grbg **head, size_t nmemb, size_t size, int free)
{
	t_grbg *last;
	void *new;

	new = ft_calloc(nmemb, size);
	if (!new)
	{
		ft_putstr_fd("memory allocation error\n", 2);
		//set exitstatus, free stuff
		return ;
	}
	if (!(*head)) //
	{
		//add_grbg_node();//@Deniz: initialize all to 0
		(*head)->ptr=new;
		(*head)->flg=free;
	}

}

t_grbg *add_grbg_node()
{
	
}
