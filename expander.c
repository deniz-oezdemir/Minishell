/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:41:31 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/22 21:40:58 by ecarlier         ###   ########.fr       */
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
char	**expander(char **str)
{

}
/*
1) Si le char actuel est ' et que dbq est 0 (pas de guillemets double ouvert)
alors sgq est mis a 1 (sinon 0)
*/
char *expand_var(char *str)
{
	int	sgq;
	int	dbq;
	int	i;
	char	*sub_str;

	sgq = 0;
	dbq = 0;

	while (str && str[++i])
	{
		sgq = (sgq + (!dbq && str[i] == '\'')) % 2; //1)
		dbq = (dbq + (!sgq && str[i] == '\"')) % 2;
		if (!sgq && str[i] == '$' && str[i + 1]) //si aucune single quote est ouverte
		{

		}
	}
}


/*
I need
ptr : A pointer to the dollar sign marking the beginning of the variable
var_len : lenght of the worf to expand
env : the current env (get it from prompt->envp )

Goes the current env and tries to find the name of the variable
using ft_strncmp
If it finds a potential match, it checks if the next char is =

*/
static char *get_substr_var(char *str, int len, char **env)
{
	char *temp;
	int i = 0;

	//temp = malloc(sizeof(char *) * len + 1);
	while (**env)
	{
		if (!ft_strncmp(str + 1, *env, len))
		{
			if ((*env + len) == '=')
			{

			}
			env++;
		}
		else
			temp = NULL;
	}

}
