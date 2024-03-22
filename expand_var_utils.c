/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:43:45 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/22 21:59:02 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*don't know what to do with the ? */
/*Gets the lenght of the var to expand, starting from $*/
int	get_len_var(char *str)
{
	int i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		i++;
	}
	return (i - 1);
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
static char *get_substr_var(char *str, int len, char **env)
{
	while (**env)
	{
		if (!ft_strncmp(str + 1, *env, len))
		{
			if (*(*env + len) == '=')
			{
				return (*env + len + 1);
			}
			env++;
		}
	}
	return ("");
}
