/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:12:21 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/14 14:56:04 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_prompt_struct(t_prompt *prompt, char **envp)
{
	//t_prompt *prompt;

	prompt->input_string = NULL;
	prompt->commands = NULL;
	prompt->cmd_list = NULL;
	prompt->pid = -1;
	//prompt->envp = get_env(envp); //todo
	init_env(prompt, envp);
}

int	init_env(t_prompt *prompt, char **env)
{
	int	i;

	i = 0;
	prompt->envp = ft_calloc((get_len_arr(env) +1), sizeof(char *));
	while (env[i])
	{
		prompt->envp[i] = ft_strdup(env[i]);
		if (!prompt->envp[i])
		{
			printf("Error env");
			return (0); //return failure
		}
		i++;
	}
	prompt->envp[i] = NULL; // or env[i] = NULL;??
	//return succes
	return (1);
}
