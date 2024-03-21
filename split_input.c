/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:39:22 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/21 15:46:28 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*exemple input = "ls -l | grep 'file.txt'" */


/*Parcourt la chaine et compte le nombre de char speciaux (> >> < << |) qui sont attaches*/
static int special_len(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i]) {
		if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
		{
			if (str[i - 1] != ' ' || str[i + 2] != ' ')
				count++;
			i += 2;
		}
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		{
			if (str[i - 1] != ' ' || str[i + 1] != ' ')
				count++;
		}
		i++;
	}
	return (count);
}
/*
    char str2[] = "commande sortie.txt>>"; // commande sortie.txt >>
	char str4[] = "commande <sortie.txt"; // commande < sortie.txt
	char str5[] = "commande sortie.txt>"; // commande sortie.txt >
	char str6[] = "commande |sortie.txt"; // commande | sortie.txt
    char str7[] = "commande| sortie.txt"; // commande | sortie.txt
    char str1[] = "commande <<sortie.txt"; // commande << sortie.txt
    char str3[] = "commande <<sortie.txt>>"; // commande << sortie.txt>>
*/
char *add_space(char *str)
{
	int i;
	int j;
	int len_str;
	char *new_str;

	i = 0;
	j = 0;
	len_str = ft_strlen(str) + special_len(str) + 1;
	new_str = (char *)malloc(sizeof(char) * len_str);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
		{
			if (i == 0 || str[i - 1] != ' ')
			{
				new_str[j++] = ' ';
				new_str[j++] = str[i++];
				new_str[j++] = str[i++];
			}
			else if(str[i + 2] != ' ')
			{
				new_str[j++] = str[i++];
				new_str[j++] = str[i++];
				new_str[j++] = ' ';
			}
		}
		else if ((str[i] == '>' || str[i] == '<' || str[i] == '|') && str[i - 1] != ' ')
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
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

static int	ft_count_words(const char *str, char *sep)
{
	int count = 0;
	int i = 0; //parcourir la chaine
	int	sgq = 0; //Guillemets simple (Ouvert =1, ferme = 0)
	int	dbq = 0;
	while (str[i] != '\0') //index actuel dans la chaine de char s
	{
		if (!ft_strchr(sep, str[i])) //verifie si char act n'est pas dans la sep
		{
			count++; //nouveau mot
			while ((!ft_strchr(sep, str[i]) || sgq) && str[i] != '\0')
			//(si pas un del ou sql ouvert) ET pas fin de la chaine
			{
				//si dbq ferme ET on trouve ' ou ''
				if (!dbq && (str[i] == '\"' || str[i] == '\''))
					dbq = str[i];
				if (str[i] == dbq)
					sgq = (sgq + 1) % 2; //sgq est inverse
				//sgq = (sgq + (str[i]== dbq)) % 2;
				dbq = dbq * (sgq != 0); //ferme "" si '
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

static char	**ft_create_substrs(char **aux, char const *s, char *set)
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
			aux[word_index++] = "\0";
		else
			aux[word_index++] = ft_substr(s, start_index, i - start_index);
	}
	aux[word_index] = NULL;
	return (aux);
}

char	**split_input(char *str)
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
		printf("Quote not properly closed\n");
		return (NULL);
	}
	arr = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!arr)
		return (NULL);
	arr = ft_create_substrs(arr, str, " ");
	arr[word_count] = NULL;
	printf("\narray : ");
	print_str_array(arr);
	return (arr);

}
