/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:25:12 by denizozd          #+#    #+#             */
/*   Updated: 2024/03/18 18:49:16 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t get_env_len(const char *s)
{
	size_t l;

	l = 0;
	if (!s)
		return (0);
	while(s[l] && s[l] != '=') //different
		l++;
	return (l);
}


int	cstm_unset(t_cmmnds *cmd_data)
{
	int	i;
	int	j;

	i = 0;
	if (!cmd_data->prompt->envp || !cmd_data->full_command)
		return (1);
	while (cmd_data->prompt->envp[i])
	{
		j = 1;
		while(cmd_data->full_command[j] && strcmp(cmd_data->full_command[j], "_"))
		{
			if (!ft_strncmp(cmd_data->prompt->envp[i], cmd_data->full_command[j], get_len_env(cmd_data->prompt->envp[i])) &&
					get_len_env(cmd_data->prompt->envp[i]) == ft_strlen(cmd_data->full_command[j]))
				remove_str_from_arr(cmd_data->prompt->envp, i, 1); //rem_str_from_arr missing -> already written by Leo?
			j++;
		}
		i++;
	}
}
