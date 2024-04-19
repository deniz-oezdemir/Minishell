/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:35:29 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/19 18:48:19 by denizozd         ###   ########.fr       */
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
	str = grbg_strjoin(name, "=");
	if (!str)
		return (NULL);
	l = ft_strlen(str);
	while(prompt->envp[i])
	{
		if (!ft_strncmp(prompt->envp[i], str, l))
		{
			env_var = grbg_strdup(prompt->envp[i] + l);
			//if (str)
			//	free(str);
			return (env_var);
		}
		i++;
	}
	//if (str)
	//	free(str);
	return (NULL);
}

void modify_envp(t_prompt *prompt, char *name, char *insert, int f_free_name)
{
	int	i;
	char *str;;

	i = 0;
	if (!prompt->envp || !insert || !name) //different
		return ;
	str = grbg_strjoin(name, "="); //different
	if (!str)
		return ;
	while (prompt->envp[i])
	{
		if (!ft_strncmp(prompt->envp[i], str, ft_strlen(str)))
		{
			//free(prompt->envp[i]);
			prompt->envp[i] = grbg_strjoin(str, insert);
		}
		i++;
	}
	/*if (insert)
		free(insert);
	if (name && f_free_name)
		free(name);
	if (str)
		free(str);*/
}

int	go_home_dir(t_prompt *prompt)
{
	char	*home_dir;
	char	*cwd_before;
	char	*cwd_after;

	home_dir = get_envp(prompt, "HOME");
	if (!home_dir)
		return(print_err_msg_lng("cd", "not set", "HOME"));
	cwd_before = (char *)getcwd(NULL, 0);
	collect_grbg(cwd_before);
	modify_envp(prompt, "OLDPWD", cwd_before, 0);
	chdir(home_dir);
	cwd_after = (char *)getcwd(NULL, 0);
	collect_grbg(cwd_after);
	modify_envp(prompt, "PWD", cwd_after, 0);
	//free(home_dir);
	return (0);
}

int go_back_dir(t_prompt *prompt)
{
	char	*old_dir;
	char	*cwd_before;
	char	*cwd_after;

	old_dir = get_envp(prompt, "OLDPWD");
	if (!old_dir)
		return(print_err_msg_lng("cd", "not set", "OLDPWD"));
	ft_printf("%s\n", old_dir);
	cwd_before = (char *)getcwd(NULL, 0);
	collect_grbg(cwd_before);
	modify_envp(prompt, "OLDPWD", cwd_before, 0);
	chdir(old_dir);
	cwd_after = (char *)getcwd(NULL, 0);
	collect_grbg(cwd_after);
	modify_envp(prompt, "PWD", cwd_after, 0);
	//if (old_dir)
	//	free(old_dir);
	return (0);
}

int cstm_cd(t_cmddat *cmd_data)
{
	DIR *dir_user;
	char	*cwd_before;
	char	*cwd_after;

	if (cmd_data->full_command)
	{
		if (!cmd_data->full_command[1])
			return(go_home_dir(cmd_data->prompt));
		else if(!ft_strcmp(cmd_data->full_command[1], "-"))
			return(go_back_dir(cmd_data->prompt));
	}
	cwd_before = (char *)getcwd(NULL, 0);
	collect_grbg(cwd_before);
	modify_envp(prompt, "OLDPWD", cwd_before, 0);
	dir_user = opendir(cmd_data->full_command[1]);
	if (!dir_user)
		return(print_err_msg_lng(cmd_data->full_command[0], "No such file or directory", cmd_data->full_command[1])); //compare bash err msg
	if (chdir(cmd_data->full_command[1]) == -1)
		return(print_err_msg_lng(cmd_data->full_command[0], "No such file or directory", cmd_data->full_command[1])); //compare bash err msg
	closedir(dir_user);
	cwd_after = (char *)getcwd(NULL, 0);
	collect_grbg(cwd_after);
	modify_envp(prompt, "PWD", cwd_after, 0);
	return (0);
}
