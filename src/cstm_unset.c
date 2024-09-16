/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:25:12 by denizozd          #+#    #+#             */
/*   Updated: 2024/09/16 19:52:16 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	get_len_env(const char *s)
{
	size_t	l;

	l = 0;
	if (!s)
		return (0);
	while (s[l] && s[l] != '=')
		l++;
	return (l);
}

int	cstm_unset(t_cmddat *cmd)
{
	int		i;
	int		j;
	char	**envs;

	i = 0;
	envs = cmd->prompt->envp;
	if (!envs || !cmd->full_cmd)
		return (1);
	while (envs[i])
	{
		j = 1;
		while (cmd->full_cmd[j] && ft_strcmp(cmd->full_cmd[j], "_"))
		{
			if (!ft_strncmp(envs[i], cmd->full_cmd[j], get_len_env(envs[i]))
				&& get_len_env(envs[i]) == ft_strlen(cmd->full_cmd[j]))
				del_str(envs, i, 1);
			j++;
		}
		i++;
	}
	return (0);
}
