/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:45:17 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/21 20:09:01 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* no garbage collection for any functions in this file as they do not leak */

char	*get_path_cmds(t_cmddat *cmd, char **ev)
{
	//printf("here\n");
	char	*path;
	if (get_builtin_nbr(cmd) != 0)
		return (NULL);
	if (!access(cmd->full_command[0], 1))
		return (ft_strdup(cmd->full_command[0]));
	//printf("full")
	path = get_path(cmd->full_command[0], ev);
	return (path);
}

/* Get the full path of the command by searching through the PATH variable:
Searches through the PATH variable to find the full path of
the command (where it is executed),
returns the full path (including the command) if found, or
NULL if the command is not in any of the specified paths. */
char	*get_path(char *cmd, char **ev)
{
	char	**all_paths;
	char	*path;
	char	*path_part;
	size_t		i;

	i = 0;

	while (ev[i] && ft_strnstr(ev[i], "PATH", 4) == 0) //PATH can not be found if unset PATH
		i++;
	if (i == get_len_arr(ev))
		return (NULL);
	all_paths = ft_split(ev[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		path_part = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(path, F_OK) == 0)
		{
			free_split(all_paths);
			//print_char_array(path);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(all_paths);
	return (NULL);
}

/* Frees the memory allocated for an array of strings such as
the one created with ft_split. */
void	free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	add_last_cmd_to_envp(t_prompt *prompt)
{
	int	l;

	l = 0;
	if (!prompt->cmd_list->data->full_command)
		return ;
	l = get_len_arr(prompt->cmd_list->data->full_command);
	if (l)
		modify_envp(prompt, "_", grbg_strdup(prompt, prompt->cmd_list->data->full_command[l - 1]));
}
