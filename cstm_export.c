/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:08:21 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/09 17:05:38 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cstm_export(t_cmddat *cmd)
{
	int	r;
	int	i;
	int	id_len;

	r = 0;
	i = 1;
	id_len = 0;
	if (get_len_arr(cmd->full_command) == 1) // no arguments
		return (print_sorted_export(cmd));
	if (!cmd->prompt->envp && get_len_arr(cmd->full_command) > 1
		&& get_len_id(cmd->full_command[i], 0)) // uninitiaized envp - @Leo: is this even possible?
		cmd->prompt->envp = add_str_to_arr(cmd->prompt->envp,
				cmd->full_command[i++]);
	while (cmd->full_command[i])
	{
		id_len = get_len_id(cmd->full_command[i], 1);
		if (id_len)
			scan_envp(cmd, cmd->full_command[i], id_len); // why i=1 not i=0?
		else
			r = 1;
		i++;
	}
	return (r);
}

int	print_sorted_export(t_cmddat *cmd)
{
	int		i;
	int		l;
	int		j;
	char	*tmp;
	char	**env_sort = NULL;
printf("c1\n");
	i = 0;
	l = 0;
	if (!cmd->prompt->envp)
		return (0);
	init_env_sort(cmd->prompt->envp, env_sort);
	printf("env_sort[1]: %s\n", env_sort[1]);
printf("c2\n");
	l = get_len_arr(env_sort);
	while (i < l)
	{
		j = i + 1;
		while (j < l)
		{
			if (ft_strcmp(env_sort[i], env_sort[j]) > 0)
			{
				tmp = env_sort[i];
				env_sort[i] = env_sort[j];
				env_sort[j] = tmp;
			}
			j++;
		}
	}
printf("c3\n");
	i = 0;
printf("env_sort[1]: %s\n", env_sort[1]);
	while (env_sort[i])
	{
printf("c4\n");
		if (ft_strncmp(env_sort[i], "_=", 2))
			print_line_sort_export(env_sort[i], cmd);
		i++;
printf("c5\n");
	}
	//free env_sort
	return (0);
}

/*Returns:
  - 1 if the initialization is successful.
  - 0 if an error occurs during memory allocation or copying.
*/
int	init_env_sort(char **env, char **env_sort)
{
	int	i;

	i = 0;
	env_sort = ft_calloc((get_len_arr(env) + 1), sizeof(char *));
	if (!env_sort)
	{
		printf("Error allocating memory for env_sort\n");
		return (0); //return failure
	}
	while (env[i])
	{
		env_sort[i] = ft_strdup(env[i]);
		if (!env_sort[i])
		{
			//free_char_array(env_sort);
			printf("Error env_sort");
			return (0); //return failure
		}
		i++;
	}
	env_sort[i] = NULL; // or env[i] = NULL;??
	//return succes
	return (1);
}

void	print_line_sort_export(char *str, t_cmddat *cmd)
{
	size_t	l;
printf("c3.1\n");
	l = get_len_id(str, 0);
printf("c3.2\n");
	ft_putstr_fd("declare -x ", cmd->outfile);
	if (l && l != ft_strlen(str)) // export TEST=hello
	{
		write(cmd->outfile, str, l);
		ft_putstr_fd("=\"", cmd->outfile);
		ft_putstr_fd(str + l + 1, cmd->outfile);
		ft_putstr_fd("\"", cmd->outfile);
	}
	else if (l) // export test
		write(cmd->outfile, str, l);
	else // l=0 because of error or empty id
		ft_putstr_fd(str, cmd->outfile);
	ft_putstr_fd("\n", cmd->outfile); //
}


int	print_export(t_cmddat *cmd)
{
	int	i;

	i = 0;
	while (cmd->prompt->envp && cmd->prompt->envp[i])
	{
		if (ft_strncmp(cmd->prompt->envp[i], "_=", 2))
			print_line_export(cmd, i);
		i++;
	}
	return (0);
}

void	print_line_export(t_cmddat *cmd, int i)
{
	size_t	l;

	l = get_len_id(cmd->prompt->envp[i], 0);
	ft_putstr_fd("declare -x ", cmd->outfile);
	if (l && l != ft_strlen(cmd->prompt->envp[i])) // export TEST=hello
	{
		write(cmd->outfile, cmd->prompt->envp[i], l);
		ft_putstr_fd("=\"", cmd->outfile);
		ft_putstr_fd(cmd->prompt->envp[i] + l + 1, cmd->outfile);
		ft_putstr_fd("\"", cmd->outfile);
	}
	else if (l) // export test
		write(cmd->outfile, cmd->prompt->envp[i], l);
	else // l=0 because of error or empty id
		ft_putstr_fd(cmd->prompt->envp[i], cmd->outfile);
	ft_putstr_fd("\n", cmd->outfile); //
}

int	get_len_id(char *str, int msg)
{
	int		i;
	int		e;
	char	*tmp;

	i = 0;
	e = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[0]))
			e = 1;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			e = 1;
		i++;
	}
	if (e || !i)
	{
		if (msg)
		{
			tmp = ft_strjoin("`", str);
			tmp = add_to_str(&tmp, "'");
			print_err_msg_lng("export", tmp, "not a valid identifier");
			if (tmp)
				free(tmp);
		}
		i = 0;
	}
	return (i);
}

int	scan_envp(t_cmddat *cmd, char *str, int id_len)
{
	int	i;
	int	envp_id_len;

	i = 0;
	while (cmd->prompt->envp[i])
	{
		envp_id_len = get_len_id(cmd->prompt->envp[i], 0);
		if (envp_id_len == id_len && !ft_strncmp(cmd->prompt->envp[i], str,
				id_len)) // if VAR exists, replace it
		{
			if (ft_strchr(str, '='))
				modify_envp(cmd->prompt, ft_substr(cmd->prompt->envp[i], 0,
						envp_id_len + 1), ft_strdup(str + envp_id_len + 1), 1);
			break ;
		}
		else if (i == get_len_arr(cmd->prompt->envp) - 1)
			// else if at end of envp, add it to the end
		{
			cmd->prompt->envp = add_str_to_arr(cmd->prompt->envp, str);
			break ;
		}
		i++;
	}
	return (0);
}

char	*add_to_str(char **str, char *add)
{
	char	*new;

	if (!add)
	{
		new = ft_strdup(*str);
		return (new);
	}
	if (!str || !*str)
	{
		new = ft_strdup(add);
		return (new);
	}
	new = ft_strjoin(*str, add);
	free(*str);
	return (new);
}
