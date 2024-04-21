/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:39:22 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/21 15:48:34 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Parcourt la chaine et compte le nombre de char speciaux (> >> < << |) qui sont attaches*/

/*
  Calculates and returns the special length of the string `str`,
  which represents the number of special characters that are not
  preceded or followed by a space.

  Parameters:
    - str: Pointer to the string to calculate the special length for.

  Returns:
    - The number of special characters that are not preceded or followed
	by a space in the string.
*/

static int special_len(char *str) {
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i + 1] && (str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
		{
			if (i > 0 && str[i - 1] != ' ')
				count++;
			if (str[i + 2] && str[i + 2] != ' ')
				count++;
			i += 1;
		}
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		{
			if (i > 0 && str[i - 1] != ' ')
				count++;
			if (str[i + 1] && str[i + 1] != ' ')
				count++;
		i++;
		}
		i++;
	}
	count++;
	return (count);
}


char *add_space(char *str)
{
	int i;
	int j;
	int len_str;
	char *new_str;
	i = 0;
	j = 0;




	len_str = ft_strlen(str) + special_len(str) + 1;
	//new_str = (char *)malloc(sizeof(char) * len_str);
	new_str = (char *)get_grbg(prompt, len_str, sizeof(char));
	if (!new_str)
		return (NULL);

	int sgq = 0;
	int dbq = 0;

	while (str[i])
	{
		sgq = (sgq + (!dbq && str[i] == '\'')) % 2;
		dbq = (dbq + (!sgq && str[i] == '\"')) % 2;
		if (!sgq && !dbq)
		{
			if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
			{
				if (str[i + 2] != ' ' && i + 2 < ft_strlen(str))
				{
					new_str[j++] = str[i++];
					new_str[j++] = str[i++];
					new_str[j++] = ' ';
				}
				else if (i == 0 || str[i - 1] != ' ')
				{
					new_str[j++] = ' ';
					new_str[j++] = str[i++];
					new_str[j++] = str[i++];
				}
				else
				{
					new_str[j++] = str[i++];
					new_str[j++] = str[i++];
				}
			}
			else if (i != 0 && (str[i] == '>' || str[i] == '<' || str[i] == '|') && str[i - 1] != ' ')
			{
				new_str[j++] = ' ';
				new_str[j++] = str[i++];
			}
			else if ((str[i] == '>' || str[i] == '<' || str[i] == '|') && str[i + 1] != ' ')
			{
				new_str[j++] = str[i++];
				new_str[j++] = ' ';
			}
			else
			{
			new_str[j++] = str[i++];
			}
		}
		else
		{
			new_str[j++] = str[i++];
		}
	}
	new_str[j] = '\0';
	//free(str);
	return (new_str);
}

/*
Counts the number of words in the given string `str`, considering a set of separators defined by `sep`.
It handles cases where words might be enclosed within single or double quotes, ensuring they are not counted separately.
If there's a mismatch in quotes, it returns -1 to indicate an error.
*/
static int	ft_count_words(const char *str, char *sep)
{
	int	count = 0;
	int	i = 0; //parcourir la chaine
	int	sgq = 0; //Guillemets simple (Ouvert =1, ferme = 0)
	int	dbq = 0;

	while (str[i] != '\0') //index actuel dans la chaine de char s
	{
		if (!ft_strchr(sep, str[i]))
		{
			count++;
			while ((!ft_strchr(sep, str[i]) || sgq) && str[i] != '\0')
			{
				if (!dbq && (str[i] == '\"' || str[i] == '\''))
					dbq = str[i];
				if (str[i] == dbq)
					sgq = (sgq + 1) % 2;
				dbq = dbq * (sgq != 0);
				i++;
			}
			if (sgq)
				return (-1);
		}
		else
			i++;
	}
	return (count);
}

/*Create */
static char	**ft_create_substrs(t_prompt *prompt, char **aux, char const *s, char *set)
{
	int		s_len;
	int		i = 0; // Index courant dans la chaîne s
	int		start_index = 0; // Index de début du mot en cours
	int		word_index = 0; // Index dans le tableau de mots
	int		sgq = 0; // sgq pour guillemet simple
	int		dbq = 0; // dbq pour guillemet double

	s_len = ft_strlen(s);
	while (s[i])
	{
		while (ft_strchr(set, s[i]) && s[i] != '\0')
			i++;
		start_index = i;
		while ((!ft_strchr(set, s[i]) || sgq || dbq) && s[i])
		{
			sgq = (sgq + (!dbq && s[i] == '\'')) % 2;
			dbq = (dbq + (!sgq && s[i] == '\"')) % 2;
			i++;
		}
		if (start_index >= s_len)
			aux[word_index++] = NULL;
		else
			aux[word_index++] = grbg_substr(prompt, s, start_index, i - start_index);
	}
	//aux[word_index] = NULL; //fixed "exit "
	return (aux);
}
/* Split the input read from the readline and put it into
	char		**commands; from the original prompt struct
*/
char	**split_input(char *str, t_prompt *prompt)
{
	char	**arr;
	int		word_count;

	if (!str)
		return (NULL);
	if (ft_isspace(*str))
		str++;
	word_count = ft_count_words(str, " ");
	if (word_count == -1)
	{
		printf("Syntax error: unclosed quote in argument\n");
		return (NULL);
	}
	//arr = (char **)malloc(sizeof(char *) * (word_count + 1));
	arr = get_grbg(prompt, word_count + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	arr = ft_create_substrs(prompt, arr, str, " ");
	arr[word_count] = NULL; //@Leo: how is this different from aux[word_index] = NULL above?
	// free(str);
	return (arr);
}
