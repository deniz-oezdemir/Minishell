/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:25:12 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/24 15:05:42 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t get_len_env(const char *s)
{
	size_t l;

	l = 0;
	if (!s)
		return (0);
	while(s[l] && s[l] != '=') //different
		l++;
	return (l);
}


int	cstm_unset(t_cmddat *cmd_data)
{
	int	i;
	int	j;

	i = 0;
	if (!cmd_data->prompt->envp || !cmd_data->full_cmd)
		return (1);
	while (cmd_data->prompt->envp[i])
	{
		j = 1;
		while(cmd_data->full_cmd[j] && ft_strcmp(cmd_data->full_cmd[j], "_"))
		{
			if (!ft_strncmp(cmd_data->prompt->envp[i], cmd_data->full_cmd[j], get_len_env(cmd_data->prompt->envp[i])) &&
					get_len_env(cmd_data->prompt->envp[i]) == ft_strlen(cmd_data->full_cmd[j]))
				del_str(cmd_data->prompt->envp, i, 1);
			j++;
		}
		i++;
	}
	return 0;
}
