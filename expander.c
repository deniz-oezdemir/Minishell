/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:41:31 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/21 17:32:55 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Expands environment variables in the array of strings `str` using
  the environment variables `ev`.
  It creates a new array with expanded strings and returns it.

  Parameters:
    - str: Array of strings to be expanded.
    - ev:  Array of strings representing environment variables.

  Returns:
    - A new array of strings with expanded environment variables.
*/

char	**expander(t_prompt *prompt, char **str, char **ev)
{
	int		i;
	char	**temp;

	temp = get_grbg(prompt, get_len_arr(str) + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	i = 0;
	while (str[i])
	{
		temp[i] = expand_var(prompt, str[i], ev);
		i++;
	}
	temp[i] = NULL;
	i = 0;
	return (temp);
}


/*
Check if inside single quote -> meaning does not need expanding
1) Si le char actuel est ' et que dbq est 0 (pas de guillemets double ouvert)
alors sgq est mis a 1 (sinon 0)
*/

/*
  Expands environment variables in the string `str` using
  the environment variables `ev`.
  It modifies the original string in-place and returns it.

  Parameters:
    - str: Pointer to the string to be expanded.
    - ev:  Array of strings representing environment variables.

  Returns:
    - Pointer to the modified string with expanded environment variables.
*/
char *expand_var(t_prompt *prompt, char *str, char **ev)
{
	int		sgq;
	int		dbq;
	int		i;
	int		len;
	char	*nb;
	char	*sub_str;

	nb = 0;
	sub_str = NULL;
	sgq = 0;
	dbq = 0;
	i = 0;

	if (ft_strcmp(str, "$") && ft_strlen(str) == 3)
		return (str);

	while (str[i])
	{
		sgq = (sgq + (!dbq && str[i] == '\'')) % 2;
		dbq = (dbq + (!sgq && str[i] == '\"')) % 2;
		if (!sgq && str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
		{
			if (str[i + 1] == '?')
			{
				nb = grbg_itoa(prompt, exitstatus);
				if (!nb)
					return (NULL);
				len = ft_strlen(nb);
				sub_str = create_sub(str, i, nb, len);
				collect_grbg(prompt, sub_str);
			}
			else
			{
				//printf("HERE\n");
				len = get_len_var(str, i + 1);
				sub_str = create_sub_var(str, i, ev, len);
				collect_grbg(prompt, sub_str);
				if (sub_str == NULL)
				{
					str = NULL;
					//printf("HERE\n");
					break;

				}

			}
			str = sub_str;
		}
		i++;
	}
	// write(1, "1", 1);
	// printf("sub_str : %s\n",sub_str);
	// printf("str : %s\n",str);
	if (sub_str)
		return (sub_str);
	else
		return (str);
}
