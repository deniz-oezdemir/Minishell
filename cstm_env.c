/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:51:04 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/09 18:28:00 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cstm_env(t_cmddat *cmd_data)
{
	int	i;

	i = -1;
	if(cmd_data->prompt->envp == NULL)
		return (1);
	while (cmd_data->prompt->envp[++i]) //different
	{
		if (ft_strchr(cmd_data->prompt->envp[i], '='))
		{
			ft_putstr_fd(cmd_data->prompt->envp[i], cmd_data->outfile);
			ft_putstr_fd("\n", cmd_data->outfile);
		}
	}
	return (0);
}
