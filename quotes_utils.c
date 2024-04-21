/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:39:46 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/21 15:48:02 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Removes unnecessary quotes from the commands stored in the prompt.
  It iterates over each command, trims unnecessary quotes from its arguments,
  and updates the prompt's command data accordingly.

  Parameters:
    - prompt: Pointer to the prompt containing the commands to be processed.

  Returns:
    - None.
*/
void	get_rid_quotes(t_prompt	*prompt)
{
	char		**temp;
	char		*trim_cmd;
	int			i;
	int			len_arr;
	t_node		*current_node;
	t_cmddat	*cmd_data;

	current_node = prompt->cmd_list;
	while (current_node != NULL)
	{
		cmd_data = current_node->data;
		i = 0;
		len_arr = get_len_arr(cmd_data->full_command);
		temp = get_grbg(len_arr + 1, sizeof(char *));
		if (!temp)
			return ;
		while (cmd_data->full_command[i])
		{
			trim_cmd = get_trimmed(cmd_data->full_command[i], 0, 0);
			temp[i] = trim_cmd;
			i++;
		}
		cmd_data->full_command = temp;
		current_node = current_node->next;
	}
}

/*
  Removes unnecessary quotes from a str while preserving quoted substrings.
  It returns a new dynamically allocated string containing the trimmed result.

  Parameters:
    - s1: Pointer to the input string to be trimmed.
    - squote: Integer representing the state of single quotes in the string.
    - dquote: Integer representing the state of double quotes in the string.

  Returns:
    - Pointer to the dynamically allocated trimmed string.
*/
char	*get_trimmed(char const *s1, int squote, int dquote)
{
	int		count;
	int		i[2];
	char	*trimmed;

	i[1] = -1;
	i[0] = 0;
	count = malloc_len(s1);
	if (!s1 || count == -1)
		return (NULL);
	//trimmed = malloc(sizeof(char) * (ft_strlen(s1) - count + 1));
	trimmed = get_grbg(prompt, ft_strlen(s1) - count + 1, sizeof(char));
	if (!trimmed)
		return (NULL);
	while (s1[i[0]])
	{
		squote = (squote + (!dquote && s1[i[0]] == '\'')) % 2;
		dquote = (dquote + (!squote && s1[i[0]] == '\"')) % 2;
		if ((s1[i[0]] != '\"' || squote) && (s1[i[0]] != '\'' || dquote) \
			&& ++i[1] >= 0)
			trimmed[i[1]] = s1[i[0]];
		i[0]++;
	}
	trimmed[++i[1]] = '\0';
	return (trimmed);
}

/*
  Counts the number of unnecessary quotes in the string `str`.
  It checks the consistency of quotes and returns the count.

  Parameters:
    - str: Pointer to the input string to be checked.

  Returns:
    - Number of unnecessary quotes in the string.
*/
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

/*BACKUP*/
//free(prompt->commands); //@Leo: to be deleted if below works as intended
//free_char_array(prompt->commands); //@Leo: this fixed a leak when exit - please double check //@Deniz: should be unnecessary with gc

// void	get_rid_quotes(t_prompt	*prompt)
// {
// 	char	**temp;
// 	char	*trim_cmd;
// 	int		i;
// 	int		len_arr;
// 	if (prompt->commands == NULL)
// 		return ;
// 	len_arr = get_len_arr(prompt->commands);
// 	//temp = malloc(sizeof(char *) * (len_arr + 1));
// 	temp = get_grbg(len_arr + 1, sizeof(char *));
// 	if (!temp)
// 		return ;
// 	i = 0;
// 	while (prompt->commands[i])
// 	{
// 		trim_cmd = get_trimmed(prompt->commands[i], 0, 0);
// 		temp[i] = trim_cmd;
// 		i++;
// 	}
// 	temp[i] = NULL;
// 	//free(prompt->commands); //@Leo: to be deleted if below works as intended
// 	//free_char_array(prompt->commands); //@Leo: this fixed a leak when exit - please double check //@Deniz: should be unnecessary with gc
// 	prompt->commands = temp;
// }
