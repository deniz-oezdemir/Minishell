/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:39:22 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/24 17:05:55 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	special_len(char *str, int count, size_t i)
{
	while (str[i] && str[i + 1])
	{
		if (str[i + 1] && ((str[i] == '>' && str[i + 1] == '>')
				|| (str[i] == '<' && str[i + 1] == '<')))
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

// void	add_spaces(char *str, char *new_str, int sgq, int dbq)
// {
// 	size_t	i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		sgq = (sgq + (!dbq && str[i] == '\'')) % 2;
// 		dbq = (dbq + (!sgq && str[i] == '\"')) % 2;
// 		if (!sgq && !dbq)
// 		{

// 		}
// 	}

// }


// char *add_space(t_prompt *prompt, char *str)
// {

// 	int len_str;
// 	char *new_str;

// 	len_str = ft_strlen(str) + special_len(str) + 1;
// 	new_str = (char *)get_grbg(prompt, len_str, sizeof(char));
// 	if (!new_str)
// 		return (NULL);

// 		if (!sgq && !dbq)
// 		{
// 			if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
// 			{
// 				if (str[i + 2] != ' ' && i + 2 < ft_strlen(str))
// 				{
// 					new_str[j++] = str[i++];
// 					new_str[j++] = str[i++];
// 					new_str[j++] = ' ';
// 				}
// 				else if (i == 0 || str[i - 1] != ' ')
// 				{
// 					new_str[j++] = ' ';
// 					new_str[j++] = str[i++];
// 					new_str[j++] = str[i++];
// 				}
// 				else
// 				{
// 					new_str[j++] = str[i++];
// 					new_str[j++] = str[i++];
// 				}
// 			}
// 			else if (i != 0 && (str[i] == '>' || str[i] == '<' || str[i] == '|') && str[i - 1] != ' ')
// 			{
// 				new_str[j++] = ' ';
// 				new_str[j++] = str[i++];
// 			}
// 			else if ((str[i] == '>' || str[i] == '<' || str[i] == '|') && str[i + 1] != ' ')
// 			{
// 				new_str[j++] = str[i++];
// 				new_str[j++] = ' ';
// 			}
// 			else
// 			{
// 			new_str[j++] = str[i++];
// 			}
// 		}
// 		else
// 		{
// 			new_str[j++] = str[i++];
// 		}
// 	}
// 	new_str[j] = '\0';
// 	return (new_str);
// }


char	*add_space(t_prompt *prompt, char *str)
{
	size_t	i;
	int		j;
	int		len_str;
	char	*new_str;
	int		sgq;
	int		dbq;

	sgq = 0;
	dbq = 0;
	i = 0;
	j = 0;

	len_str = ft_strlen(str) + special_len(str, 0, 0) + 1;
	new_str = (char *)get_grbg(prompt, len_str, sizeof(char));
	if (!new_str)
		return (NULL);
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
	return (new_str);
}

/*
Counts the number of words in the given string `str`,
considering a set of separators defined by `sep`.
It handles cases where words might be enclosed within single or double quotes,
ensuring they are not counted separately.
If there's a mismatch in quotes, it returns -1 to indicate an error.
*/
static int	ft_count_words(const char *str, char *sep, int count, int i)
{
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	while (str[i] != '\0')
	{
		if (!ft_strchr(sep, str[i]))
		{
			count++;
			while ((!ft_strchr(sep, str[i]) || q[0]) && str[i] != '\0')
			{
				if (!q[1] && (str[i] == '\"' || str[i] == '\''))
					q[1] = str[i];
				if (str[i] == q[1])
					q[0] = (q[0] + 1) % 2;
				q[1] = q[1] * (q[0] != 0);
				i++;
			}
			if (q[0])
				return (-1);
		}
		else
			i++;
	}
	return (count);
}

/*
	i[0]
	i[1] : start_index
	i[2] : word_index
*/
char	**ft_create_substrs(t_prompt *p, char **aux, char const *s, char *set)
{
	int		i[3];
	int		q[2];

	q[1] = 0;
	q[0] = 0;
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (s[i[0]])
	{
		while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
		{
			q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= (int)ft_strlen(s))
			aux[i[2]++] = NULL;
		else
			aux[i[2]++] = grbg_substr(p, s, i[1], i[0] - i[1]);
	}
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
	word_count = ft_count_words(str, " ", 0, 0);
	if (word_count == -1)
	{
		printf("Syntax error: unclosed quote in argument\n");
		return (NULL);
	}
	arr = get_grbg(prompt, word_count + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	arr = ft_create_substrs(prompt, arr, str, " ");
	arr[word_count] = NULL;
	return (arr);
}
