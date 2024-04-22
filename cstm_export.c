/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:08:21 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/22 17:07:01 by denizozd         ###   ########.fr       */
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
	if (cmd->outfile != 1) //if pipe after export
	{
		close(cmd->outfile);
		cmd->outfile = 1;
		return (0);
	}
	if (get_len_arr(cmd->full_command) == 1)
		return (print_export(cmd));
	if (!cmd->prompt->envp && get_len_arr(cmd->full_command) > 1
		&& get_len_id(cmd->prompt, cmd->full_command[i], 0)) // uninitiaized envp - @Leo: is this even possible? @deniz is this comment still valid? 10/04 @Leo: yes
		cmd->prompt->envp = add_str_to_arr(cmd->prompt, cmd->prompt->envp,
				cmd->full_command[i++]);
	while (cmd->full_command[i])
	{
		id_len = get_len_id(cmd->prompt, cmd->full_command[i], 1);
		if (id_len)
			scan_envp(cmd, cmd->full_command[i], id_len);
		else
			r = 1;
		i++;
	}
	return (r);
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

/*	if			e.g. "TEST=hello"
	else if		e.g., "export test"
	else (l=0)	because of error or rmpty command */
void	print_line_export(t_cmddat *cmd, int i)
{
	size_t	l;

	l = get_len_id(cmd->prompt, cmd->prompt->envp[i], 0);
	ft_putstr_fd("declare -x ", cmd->outfile);
	if (l && l != ft_strlen(cmd->prompt->envp[i]))
	{
		write(cmd->outfile, cmd->prompt->envp[i], l);
		ft_putstr_fd("=\"", cmd->outfile);
		ft_putstr_fd(cmd->prompt->envp[i] + l + 1, cmd->outfile);
		ft_putstr_fd("\"", cmd->outfile);
	}
	else if (l)
		write(cmd->outfile, cmd->prompt->envp[i], l);
	else
		ft_putstr_fd(cmd->prompt->envp[i], cmd->outfile);
	ft_putstr_fd("\n", cmd->outfile);
}

int	get_len_id(t_prompt *prompt, char *str, int msg)
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
			tmp = grbg_strjoin(prompt, "`", str);
			tmp = add_to_str(prompt, &tmp, "'");
			print_err_msg_lng("export", "not a valid identifier", tmp);
			//if (tmp)
				//free(tmp);
		}
		i = 0;
	}
	return (i);
}

/*	if VAR exists, replace VAR
	else if end of envp, add VAR */
int	scan_envp(t_cmddat *cmd, char *str, int id_len)
{
	size_t	i;
	int	envp_id_len;

	i = 0;
	while (cmd->prompt->envp[i])
	{
		envp_id_len = get_len_id(cmd->prompt, cmd->prompt->envp[i], 0);
		if (envp_id_len == id_len && !ft_strncmp(cmd->prompt->envp[i], str, id_len))
		{
			if (ft_strchr(str, '='))
				modify_envp(cmd->prompt, grbg_substr(cmd->prompt, cmd->prompt->envp[i], 0,
						envp_id_len), grbg_strdup(cmd->prompt, str + envp_id_len + 1));
			break ;
		}
		else if (i == get_len_arr(cmd->prompt->envp) - 1)
		{
			cmd->prompt->envp = add_str_to_arr(cmd->prompt, cmd->prompt->envp, str);
			break ;
		}
		i++;
	}
	return (0);
}

char	*add_to_str(t_prompt *prompt, char **str, char *add)
{
	char	*new;

	if (!add)
	{
		new = grbg_strdup(prompt, *str);
		return (new);
	}
	if (!str || !*str)
	{
		new = grbg_strdup(prompt, add);
		return (new);
	}
	new = grbg_strjoin(prompt, *str, add);
	//free(*str);
	return (new);
}
