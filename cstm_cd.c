/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:35:29 by denizozd          #+#    #+#             */
/*   Updated: 2024/03/25 14:31:09 by denizozd         ###   ########.fr       */
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
		return ;
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
		return(print_err_msg_lng("cd", "not set", "HOME"));
	chdir(home_dir);
	modify_envp(prompt, "PWD", (char *)getcwd(NULL, 0), 0);
	free(home_dir);
	return (0);
}

int go_back_dir(t_prompt *prompt)
{
	char	*old_dir;

	old_dir = get_envp(prompt, "OLDPWD");
	if (!old_dir)
		return(print_err_msg_lng("cd", "not set", "OLDPWD"));
	ft_printf("%s\n", old_dir);
	chdir(old_dir);
	modify_envp(prompt, "PWD", (char *)getcwd(NULL, 0), 0);
	if (old_dir)
		free(old_dir);
	return (0);
}

/* @Deniz: test cd! */
int cstm_cd(t_cmddat *cmd_data)
{
	DIR *dir_user;

	if (cmd_data->full_command)
	{
		if (!cmd_data->full_command[1])
			return(go_home_dir(cmd_data->prompt));
		else if(ft_strcmp(cmd_data->full_command[1], "-"))
			return(go_back_dir(cmd_data->prompt));
	}
	modify_envp(cmd_data->prompt, "OLDPWD", (char *)getcwd(NULL, 0), 0);
	dir_user = opendir(cmd_data->full_command[1]);
	if (!dir_user)
		return(print_err_msg_lng(cmd_data->full_command[0], "No such file or directory", cmd_data->full_command[1])); //compare bash err msg
	if (chdir(cmd_data->full_command[1]) == -1)
		return(print_err_msg_lng(cmd_data->full_command[0], "No such file or directory", cmd_data->full_command[1])); //compare bash err msg
	closedir(dir_user);
	modify_envp(cmd_data->prompt, "PWD", (char *)getcwd(NULL, 0), 0);
	return (0);
}
