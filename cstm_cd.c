/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:35:29 by denizozd          #+#    #+#             */
/*   Updated: 2024/03/25 12:11:44 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* custom getenv for the parsed environment variables in the prompt struct */
char *get_envp(t_prompt *prompt, char *name)
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
		i++;
	}
	if (str)
		free(str);
	return (NULL);
}

void modify_envp(t_prompt *prompt, char *name, char *insert, int f_free_name)
{
	int	i;
	char *str;;

	i = 0;
	if (!prompt->envp || !insert || !name) //different
		return NULL;
	str = ft_strjoin(name, "="); //different
	if (!str)
		return ;
	while (prompt->envp[i])
	{
		if (!ft_strncmp(prompt->envp[i], name, ft_strlen(name)))
		{
			free(prompt->envp[i]);
			prompt->envp[i] = ft_strjoin(name, insert);
		}
		i++;
	}
	if (insert)
		free(insert);
	if (name && f_free_name)
		free(name);
	if (str)
		free(str);
}

int	go_home_dir(t_prompt *prompt)
{
	char	*home_dir;

	home_dir = get_envp(prompt, "HOME");
	if (!home_dir)
		//add print long err
	chdir(home_dir);
	modify_envp(prompt, "PWD", getcwd(NULL, 0), 0);
	free(home_dir);
}

int go_back_dir(t_prompt *prompt)
{

}

int cstm_cd(t_cmddat *cmd_data)
{
	DIR *dir_user;

	if (cmd_data->full_command)
	{
		if (!cmd_data->full_command[1])
			return(go_home_dir(cmd_data->prompt));
		else if(ft_strcmp(cmd_data->full_command[1], "-"))
			return(go_back_dir()); //write
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
