/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:39:22 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/15 10:22:59 by ecarlier         ###   ########.fr       */
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

static void	ft_create_substrs(char	**arr_strs, char const *s, char c)
{
	char const	*tmp;

	tmp = s;
	while (*tmp)
	{
		while (*s == c)
			s++;
		tmp = s;
		while (*tmp && *tmp != c)
			tmp++;
		if (*tmp == c || tmp > s)
		{
			*arr_strs = ft_substr(s, 0, tmp - s);
			s = tmp;
			arr_strs++;
		}
	}
	*arr_strs = NULL;
}

static int	ft_count_words(char const *s, char sep)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == sep)
			s++;
		if (*s)
			count++;
		while (*s && *s != sep)
			s++;
	}
	return (count);
}

char	**split_input(char *str)
{
	char	**arr;

	arr = NULL;
	print_char_array(str);
	arr = ft_split(str, ' ');
	print_str_array(arr);
	// while (*str)
	// {
	// 	if (ft_isspace(*str))
	// 		str++;
	// 	//else if (*str == "<" || *str == ">" || *str == "|" )
	// }
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr_strs;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	arr_strs = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!arr_strs)
		return (NULL);
	ft_create_substrs(arr_strs, s, c);
	return (arr_strs);
}
