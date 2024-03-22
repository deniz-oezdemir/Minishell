/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:35:29 by denizozd          #+#    #+#             */
/*   Updated: 2024/03/22 15:25:00 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cstm_cd(t_cmddat *cmd_data)
{
	DIR *dir_user;

	if (cmd_data->full_command)
	{
		if (!cmd_data->full_command[1])
			return(go_home()); //write
		else if(ft_strcmp(cmd_data->full_command[1], "-"))
			return(go_back()); //write
	}
	cmd_data->prompt->envp = modify_envp(); //write
	dir_user = opendir(cmd_data->full_command[1]);
	if (!dir_user)
		return(print_err_msg_lng()); //write -> check bash err msg
	if (chdir(cmd_data->full_command[1]) == -1)
		return(print_err_msg_lng()); //write -> check bash err msg
	closedir(dir_user);
	cmd_data->prompt->envp = modify_envp(); //write
	return (0);
}
