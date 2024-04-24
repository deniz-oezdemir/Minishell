/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:12:21 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/24 15:07:44 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Initializes the prompt structure `prompt` with the
provided environment variables `envp`.

Parameters:
- prompt: Pointer to the prompt structure to initialize.
- envp:   Array of strings representing the environment variables.

Note: This function also initializes the environment
within the prompt structure using the `init_env` function.

Returns: None
*/
void	init_prompt_struct(t_prompt *prompt, char **envp)
{
	prompt->input_string = NULL;
	prompt->commands = NULL;
	prompt->cmd_list = NULL;
	prompt->pid = -1;
	prompt->stop = 0;
	prompt->grbg_lst = NULL;
	init_env(prompt, envp);
}

/*
Initializes the environment for the minishell by copying the provided
environment variables `env` into the `prompt->envp` array.

Parameters:
- prompt: Pointer to the prompt structure containing environment information.
- env:    Array of strings representing the environment variables.

Returns:
  - 1 if the initialization is successful.
  - 0 if an error occurs during memory allocation or copying.
*/
int	init_env(t_prompt *prompt, char **env)
{
	int	i;

	i = 0;
	prompt->envp = get_grbg(prompt, get_len_arr(env) + 1, sizeof(char *));
	if (!prompt->envp)
	{
		printf("Error allocating memory for envp\n");
		return (0);
	}
	while (env[i])
	{
		prompt->envp[i] = grbg_strdup(prompt, env[i]);
		if (!prompt->envp[i])
		{
			printf("Error env");
			return (0);
		}
		i++;
	}
	prompt->envp[i] = NULL;
	return (1);
}

/*
  Initializes a new structure t_cmddat with default values.
  Allocates memory for the structure and returns a pointer to it.

  Returns:
    - Pointer to the newly initialized t_cmddat structure.
*/
t_cmddat	*init_struct_cmd(t_prompt *prompt)
{
	t_cmddat	*ptr;

	ptr = get_grbg(prompt, 1, sizeof(t_cmddat));
	if (!ptr)
		return (NULL);
	ptr->full_cmd = NULL;
	ptr->full_path = NULL;
	ptr->infile = STDIN_FILENO;
	ptr->outfile = STDOUT_FILENO;
	ptr->prompt = prompt;
	ptr->file_open = 0;
	return (ptr);
}
