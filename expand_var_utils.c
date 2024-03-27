/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:43:45 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/27 19:00:53 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*don't know what to do with the ? */
/*
Gets the lenght of the var to expand, starting from after the$
i is the position of the string */
ssize_t	get_len_var(char *str, int i)
{
	//printf("i %d in get len\n", i);
	//printf("str %c\n", *str);
	//printf("str dans get len %s\n", str);
	ssize_t	count;
	count = 0;

		//while (*str && !ft_isspace(*str) && *str != '\"')
	// while (*str && !ft_isspace(*str) && *str != '\"' )
	// {
	// 	printf("str %c\n", *str);
	// 	count++;
	// 	str++;
	// }
	// return (count);

	while (str[i] && !ft_isspace(str[i]) && str[i] != '\"' && str[i] != '\'' )
	{
		//printf("str[%d] %c\n", i, str[i]);
		count++;
		i++;
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

/*
  Searches for the value of the environment variable
  specified by the string `str` within the array of environment variables `env`.
  It returns a pointer to the value of the environment variable.

  Parameters:
    - str:          Pointer to the string representing the environment variable.
    - var_exp_len:  Length of the environment variable to search for.
    - env:          Array of strings representing environment variables.

  Returns:
    - Pointer to the value of the environment variable if found.
    - Pointer to an empty string if the environment variable is not found.
*/
static char	*get_ptr_var(char *str, size_t var_exp_len, char **env)
{
	//printf("eneters GET PTR \n");
	//printf("str inside get ptr %s\n", str);
	while (*env)
	{
		if (!ft_strncmp(str, *env, var_exp_len)
			&& *(*env + var_exp_len) == '=')
			return (*env + var_exp_len + 1);
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

/*
  Creates a substring by expanding the environment variable specified by
  the substring in the string `str`.
  It constructs and returns a new string with the
   expanded environment variable.

  Parameters:
    - str: Pointer to the string containing the environment variable to be expanded.
    - i:   Index of the starting character of the environment variable substring.
    - ev:  Array of strings representing environment variables.
    - len: Length of the environment variable substring to expand.

  Returns:
    - Pointer to the newly created string with the expanded environment variable.
*/
char	*create_sub_var(char *str, size_t i, char **ev, ssize_t len )
{
	//ssize_t	len; //longueur de la variable a etendre
	char *s1; //partie avant $
	char *s2; // valeur de la variable a etendre
	char *s3; // apres $
	char *expanded_str;
	//char *ptr;

	//printf("len %zd\n", len);
	//printf("i = %zd\n", i);

	//printf("len %zd\n", len);
	//printf("i = %zd\n", i);

	s1 = ft_substr(str, 0, i);
	s3 = ft_substr(str, i + len + 1, ft_strlen(str) - i - len);
	s2 = ft_strdup(get_ptr_var(&str[i + 1], len, ev));

	// printf("s1: %s\n", s1);
	// printf("s2: %s\n", s2);
	// printf("s3: %s\n", s3);

	expanded_str = ft_strjoin(s1, s2);
	expanded_str = ft_strjoin(expanded_str, s3);

	//printf("expanded_str: %s\n", expanded_str);

	free(s1);
	free(s2);
	free(s3);
	//free(expanded_str);
	return (expanded_str);
}
