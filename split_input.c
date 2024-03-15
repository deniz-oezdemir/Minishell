/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:39:22 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/15 16:14:30 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*exemple input = "ls -l | grep 'file.txt'" */

#include <stdio.h>

static void print_char_array(const char arr[]) {
    printf("[");
    for (int i = 0; arr[i] != '\0'; i++) {
        printf("%c", arr[i]);
    }
    printf("]\n");
}

void print_str_array(char **arr) {
    printf("[\n");
    for (int i = 0; arr[i] != NULL; i++) {
        printf("\"%s\",\n", arr[i]);
    }
    printf("]\n");
}

// static void	ft_create_substrs(char	**arr_strs, char const *s, char c)
// {
// 	char const	*tmp;

// 	tmp = s;
// 	while (*tmp)
// 	{
// 		while (*s == c)
// 			s++;
// 		tmp = s;
// 		while (*tmp && *tmp != c)
// 			tmp++;
// 		if (*tmp == c || tmp > s)
// 		{
// 			*arr_strs = ft_substr(s, 0, tmp - s);
// 			s = tmp;
// 			arr_strs++;
// 		}
// 	}
// 	*arr_strs = NULL;
// }

// // static int	ft_count_words(char const *s, char *sep)
// // {
// // 	int	count;

// // 	count = 0;
// // 	while (*s)
// // 	{
// // 		while (ft_strchr(sep, *s))
// // 			s++;
// // 		if (*s)
// // 			count++;
// // 		while (*s && !ft_strchr(sep, *s))
// // 			s++;
// // 	}
// // 	return (count);
// // }

// static int	ft_count_words(char const *s, char sep)
// {
// 	int	count;

// 	count = 0;
// 	while (*s)
// 	{
// 		while (*s == sep)
// 			s++;
// 		if (*s)
// 			count++;
// 		while (*s && *s != sep)
// 			s++;
// 	}
// 	return (count);
// }

// char	**split_input(char *str)
// {
// 	char	**arr;

// 	// arr = NULL;
// 	print_char_array(str);
// 	arr = ft_split(str, ' ');
// 	print_str_array(arr);
// 	// while (*str)
// 	// {
// 	// 	if (ft_isspace(*str))
// 	// 		str++;
// 	//
// 	// }
// 	return (arr);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**arr_strs;
// 	int		word_count;

// 	if (!s)
// 		return (NULL);
// 	word_count = ft_count_words(s, c);
// 	arr_strs = (char **)malloc(sizeof(char *) * (word_count + 1));
// 	if (!arr_strs)
// 		return (NULL);
// 	ft_create_substrs(arr_strs, s, c);
// 	return (arr_strs);
// }

static int	ft_count_words(const char *str, char *sep)
{
	int count = 0;
	int i = 0; //parcourir la chaine
	int	sgq = 0; //Guillemets simple (Ouvert =1, ferme = 0)
	int	dbq = 0;
	while (str[i] != '\0') //s[i[0]] index actuel dans la chaine de char s
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

// static char	**ft_fill_array(char **aux, char const *s, char *set, int i[3])
// {
// 	int		s_len;
// 	int		q[2];

// 	q[0] = 0;
// 	q[1] = 0;
// 	s_len = ft_strlen(s);
// 	while (s[i[0]])
// 	{
// 		while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
// 			i[0]++;
// 		i[1] = i[0];
// 		while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
// 		{
// 			q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
// 			q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
// 			i[0]++;
// 		}
// 		if (i[1] >= s_len)
// 			aux[i[2]++] = "\0";
// 		else
// 			aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
// 	}
// 	return (aux);
// }

// char	**ft_cmdtrim(char const *s, char *set)
// {
// 	char	**arr;
// 	int		count_words;
// 	int		i[3];
// 	// int		counts[2]; //

// 	i[0] = 0; //index mpour parcourir s
// 	i[1] = 0; // suivre le nombre de mots ajoutés au tableau de chaînes de caractères.
// 	i[2] = 0; //utilisé comme un index pour ajouter des éléments au tableau de chaînes de caractères aux.
// 	// counts[0] = 0; //compter les mots
// 	// counts[1] = 0; //compter les caractères
// 	if (!s)
// 		return (NULL);
// 	count_words = ft_count_words(s, set, counts);
// 	// if (nwords == -1)
// 	// 	return (NULL);
// 	arr = malloc((count_words  + 1) * sizeof(char *));
// 	if (arr == NULL)
// 		return (NULL);
// 	arr = ft_fill_array(arr, s, set, i);
// 	arr[count_words] = NULL;
// 	return (arr);
// }



char	**split_input(char *str)
{
	char	**arr;

	arr = NULL;

    // Test avec différentes chaînes et délimiteurs


    int count1 = ft_count_words(str, " ");
    //printf("Nombre de mots dans \"%s\" : %d\n", str, count1);


    // char *str1 = "Ceci est une phrase de test";
    // char *str2 = "Ceci est "une phrase avec" des guillemets";
    // char *str3 = "Mot1|Mot2|Mot3";
    // char *str4 = "Mot1 'Mot 2'|\"Mot 3\"";



	// print_char_array(str);
	// arr = ft_split(str, ' ');
	// print_str_array(arr);
	// while (*str)
	// {
	// 	if (ft_isspace(*str))
	// 		str++;
	//
	// }
	return (arr);
}
