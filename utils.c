/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:31:31 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/24 15:16:28 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

size_t	get_len_arr(char **array)
{
	size_t	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i])
	{
		i++;
	}
	return (i);
}

int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

/*
delete a str from a string array
pos : position of the first str to del
count : how many str to delete
*/

char	**del_str(char **array, int pos, int count)
{
	int	i;
	int	buff;

	i = 0;
	while (i++ < count)
	{
		buff = pos;
		while (array[++buff])
			array[buff - 1] = array[buff];
		array[buff - 1] = NULL;
	}
	return (array);
}

char	**add_str_to_arr(t_prompt *prompt, char **arr, char *str)
{
	char	**new;
	int		l;

	l = get_len_arr(arr);
	new = get_grbg(prompt, l + 2, sizeof(char *));
	if (!new)
		return (NULL);
	new[l] = grbg_strdup(prompt, str);
	l--;
	while (l >= 0)
	{
		new[l] = grbg_strdup(prompt, arr[l]);
		l--;
	}
	return (new);
}
