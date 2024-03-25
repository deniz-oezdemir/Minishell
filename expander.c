/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:41:31 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/25 18:33:07 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* before [["echo"], ["$PWD"]]
	after [["echo"], []]
metachar ( < > | $)
ne pas traiter les metachar
A l'interieur de double quote : doit traiter $
A l'interieur de single quote : ne pas traiter $
*/
char	**expander(char **str, char **ev)
{
	int		i;
	char	**temp;

	temp = malloc(sizeof(char **) * get_len_arr(str) + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (str[i])
	{
		temp[i] = expand_var(str[i], ev);
		i++;
	}
	temp[i] = NULL;
	//printf("tmp %s\n", temp[i]);
	return (temp);
}
/*
Check if inside single quote -> meaning does not need expanding
1) Si le char actuel est ' et que dbq est 0 (pas de guillemets double ouvert)
alors sgq est mis a 1 (sinon 0)
*/
char *expand_var(char *str, char **ev)
{
	int		sgq;
	int		dbq;
	int		i;
	int		len;
	char	*sub_str;

	sub_str = NULL;
	sgq = 0;
	dbq = 0;
	i = 0;
	while (str[i])
	{
		sgq = (sgq + (!dbq && str[i] == '\'')) % 2;
		dbq = (dbq + (!sgq && str[i] == '\"')) % 2;
		if (!sgq && str[i] == '$' && str[i + 1])
		{
			len = get_len_var(str, i + 1);
			//printf("len %i \n", len);
			sub_str = create_sub_var(str, i, ev, len);
			printf("sub %s\n", str);
			free(str);
			str = sub_str;
			//printf("str %s\n", str);
		}
		i++;
	}
	if (sub_str)
		return (sub_str);
	else
		return (str);
}
