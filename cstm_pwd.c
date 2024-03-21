/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:32:03 by denizozd          #+#    #+#             */
/*   Updated: 2024/03/21 17:41:35 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cstm_pwd(t_cmddat *cmd_data)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_putstr_fd(cwd, 1); //instead of stdout (1) replace with cmd_data->outfile
	ft_putstr_fd("\n", 1); //instead of stdout (1) replace with cmd_data->outfile
	free(cwd);
	return (0);
}
