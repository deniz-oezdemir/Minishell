/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:35:29 by denizozd          #+#    #+#             */
/*   Updated: 2024/03/25 11:27:45 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* custom getenv for the parsed environment variables in the prompt struct */
char *cstm_get_envp(t_prompt *prompt, char *name)
{
	int	i;
	int l;
	char	*str;
	char	*env_var;

	i = 0;
	if (!name)
		return (NULL);
	str = ft_strjoin(name, "=");
	if (!str)
		return (NULL);
	l = ft_strlen(str);
	while(prompt->envp[i])
	{
		if (!ft_strncmp(prompt->envp[i], str, l))
		{
			env_var = ft_strdup(prompt->envp[i] + l);
			if (str)
				free(str);
			return (env_var);
		}
	}
	if (str)
		free(str);
	return (NULL);
}

int	go_home(t_cmddat *cmd_data)
{

}

int cstm_cd(t_cmddat *cmd_data)
{
	DIR *dir_user;

	if (cmd_data->full_command)
	{
		if (!cmd_data->full_command[1])
			return(go_home(void)); //write
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
