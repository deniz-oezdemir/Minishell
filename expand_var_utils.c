/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:43:45 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/23 15:24:46 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*don't know what to do with the ? */
/*
Gets the lenght of the var to expand, starting from after the$
i is the position of the string */
ssize_t	get_len_var(char *str, int i)
{
	ssize_t	count;
	printf("eneters \n");
	count = -1;
	while (*str && !ft_isspace(*str))
	{
		count++;
		str++;
	}
	return (count);
}

/*
I need
str : A pointer to the dollar sign marking the beginning of the variable
var_len : lenght of the worf to expand
env : the current env (get it from prompt->envp )

Goes the current env and tries to find the name of the variable
using ft_strncmp
If it finds a potential match, it checks if the next char is =
the returns A POINTER to the expanded variable or empty string if
no match found
*/

// static char	*get_ptr_var(char *str, size_t var_exp_len, char **env)
// {
// 	while (*env)
// 	{
// 		if (!ft_strncmp(str + 1, *env, var_exp_len)
// 			&& *(*env + var_exp_len) == '=')
// 			return (*env + var_exp_len + 1);
// 		env++;
// 	}
// 	return ("");
// }
static char *get_ptr_var(char *str, size_t len, char **env)
{
	printf("eneters GET PTR \n");
	while (*env)
	{
		//printf("inside if\n");
		if (!ft_strncmp(str + 1, *env, len))
		{
			//printf("inside if\n");
			if (*(*env + len) == '=')
			{
				printf("here");
				return (*env + len + 1);
			}
		}
		env++;
	}
	return ("");
}

/*
Concatenates the strings with the expanded var
str : original str
ptr : pointer to the expander variable
i : pos where to start to expand
*/
void	create_sub_var(char *str, size_t i, char **ev, ssize_t len )
{
	//ssize_t	len; //longueur de la variable a etendre
	char *s1; //partie avant $
	char *s2; // valeur de la variable a etendre
	char *s3; // apres $
	char *expanded_str;
	char *ptr;

	printf("len %zd\n", len);
	//printf("Enters create_sub\n");

	printf("i = %zd\n", i);
	ptr = get_ptr_var(str + i, len, ev);
	s1 = ft_substr(str, 0, i);
	s3 = ft_substr(str, i + len + 1, ft_strlen(str) - i - len);
	s2 = ft_strdup(ptr);

	printf("s1: %s\n", s1);
	printf("s2: %s\n", s2);
	printf("s3: %s\n", s3);

	expanded_str = ft_strjoin(s1, s2);
	expanded_str = ft_strjoin(expanded_str, s3);

	printf("expanded_str: %s\n", expanded_str);

	free(s1);
	free(s2);
	free(s3);
	free(expanded_str);
}
