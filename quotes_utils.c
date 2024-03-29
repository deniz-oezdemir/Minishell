/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:39:46 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/29 13:54:57 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
ft_strtrim_all*/

void	get_rid_quotes(t_prompt	*prompt)
{
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
}

char	*get_trimmed(char *str, int squote, int dquote)
{
	int	len;
	char	*trimmed;
	int	i; //parcourt la chaine str
	int j; //suivre la nouvelle chaine


	len = malloc_len(str);
	if (!str || len == -1)
		return (NULL);
	trimmed = malloc(sizeof(char *) * len + 1);
	if (!trimmed)
		return (NULL);
	while (str[i])
	{
		squote = (squote + (!dquote && str[i] == '\'')) % 2;
		dquote = (dquote + (!squote && str[i] == '\"')) % 2;
		if ((str[i] != '\"' || squote) && (str[i] != '\'' || dquote) \
		&& ++j >= 0)
		trimmed[j] = str[i];
		i++;
	}
	j++;
	trimmed[j] = '\0';
}

static int	malloc_len(char const *str)
{
	int	count;
	int	squote;
	int	dquote;
	int	i;

	count = 0;
	squote = 0;
	dquote = 0;
	i = 0;

	while (str && str[i])
	{
		squote = (squote + (!dquote && str[i] == '\'')) % 2;
		dquote = (dquote + (!squote && str[i] == '\"')) % 2;
		if ((str[i] == '\"' && !squote) || (str[i] == '\'' && !dquote))
			count++;
		i++;
	}
	if (squote || dquote)
		return (-1);
	return (count);
}
