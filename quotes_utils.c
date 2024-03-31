/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:39:46 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/31 16:26:12 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	get_rid_quotes(t_prompt	*prompt)
{
	char	**temp;
	char	*trim_cmd;
	int		i;
	int		len_arr;

	len_arr = get_len_arr(prompt->commands);
	temp = malloc(sizeof(char *) * (len_arr + 1));
	if (!temp)
		return ;
	i = 0;
	//print_str_array(prompt->commands);
	while (prompt->commands[i])
	{
		trim_cmd = get_trimmed(prompt->commands[i], 0, 0);
		temp[i] = trim_cmd;
		i++;
	}
	temp[i] = NULL;
	free(prompt->commands);
	prompt->commands = temp;
	//print_str_array(prompt->commands);
	//print_char_array(temp);

}

char	*get_trimmed(char *str, int squote, int dquote)
{
	int	len_s;
	char	*trimmed;
	int	i; //parcourt la chaine str
	int j; //suivre la nouvelle chaine

	i = 0;
	j = -1;
	len_s = malloc_len(str);
	if (!str || len_s == -1)
		return (NULL);
	trimmed = malloc(sizeof(char) * (len_s + 1));
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
	return (trimmed);
}

int	malloc_len(char const *str)
{
	int	count;
	int	squote;
	int	dquote;
	int	i;

	count = 0;
	squote = 0;
	dquote = 0;
	i = 0;
	while (str[i])
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
