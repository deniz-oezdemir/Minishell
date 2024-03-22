/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:41:31 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/22 22:50:33 by ecarlier         ###   ########.fr       */
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
	int	i;

	i = 0;
	//printf("Enters expander\n");
	while (str[i])
	{
		expand_var(str[i]);
		i++;
	}
	return (str);
}
/*
Check if inside single quote -> meaning does not need expanding
1) Si le char actuel est ' et que dbq est 0 (pas de guillemets double ouvert)
alors sgq est mis a 1 (sinon 0)
*/
char *expand_var(char *str)
{
	int	sgq;
	int	dbq;
	int	i;
	int len;
	char	*sub_str;


	//printf("Enters expand_vars\n");
	sgq = 0;
	dbq = 0;
	i = 0;
	while (str[i])
	{
		sgq = (sgq + (!dbq && str[i] == '\'')) % 2; //1)
		dbq = (dbq + (!sgq && str[i] == '\"')) % 2;
		//printf("sgq  = %d \n dbq = %d \n", sgq, dbq);
		if (!sgq && str[i] == '$' && str[i + 1]) //si aucune single quote est ouverte
		{
			printf("here\n");
			//i is the position of the var to expand
			// i +1 is after the $
			len = get_len_var(str, i + 1);
			printf("Lenght of the var to expand : %d\n", len);
			//get_substr_var()
		}
		i++;
	}
	return (str);
}


