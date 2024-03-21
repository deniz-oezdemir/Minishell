/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:51:04 by denizozd          #+#    #+#             */
/*   Updated: 2024/03/21 17:41:35 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cstm_env(t_cmddat *cmd_data)
{
	int	i;

	i = -1;
	if(cmd_data->prompt->envp == NULL) //@Leo: check here necessary or already checked somewhere else?
		return (1);
	while (cmd_data->prompt->envp[++i]) //iterating different //why do we need to check for =?
	{
		if (ft_strchr(cmd_data->prompt->envp[i], '='))
		{
			ft_putstr_fd(cmd_data->prompt->envp[i], 1); //change 1 to outfile
			ft_putstr_fd("\n", 1); //change 1 to outfile
		}
	}
	return (0);
}
