/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:08:21 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/09 12:11:29 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cstm_export(t_cmddat *cmd)
{
	int r;
	int i;
	int id_len;

	r = 0;
	i = 1;
	id_len = 0;
	if (get_len_arr(cmd->full_command) == 1) //no arguments
		return (print_export(cmd));
	if (!cmd->prompt->envp && get_len_arr(cmd->full_command) > 1 //uninitiaized envp - @Leo: is this even possible?
		&& get_len_id(cmd->full_command[i], 0))
		cmd->prompt->envp = add_str_to_array(cmd->prompt->envp, cmd->full_command[i++]);
	while(cmd->full_command[i])
	{
		id_len = get_len_id(cmd->full_command[i], 1);
		if (id_len)
			scan_envp(cmd, id_len);
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
	}
	return 0;
}

void	print_line_export(t_cmddat *cmd, int i)
{
	size_t	l;

	l = get_len_id(cmd->prompt->envp[i]);
	ft_putstr_fd("declare -x", cmd->outfile);
	if (l && l != ft_strlen(cmd->prompt->envp[i])) //export TEST=hello
	{
		write (cmd->outfile, cmd->prompt->envp[i], l);
		ft_putstr_fd("=\"", cmd->outfile);
		ft_putstr_fd(cmd->prompt->envp[i] + l + 1, cmd->outfile);
		ft_putstr_fd("\"", cmd->outfile);
	}
	else if (l) //export TEST
		write (cmd->outfile, cmd->prompt->envp[i], l);
	else
		
}

int	get_len_id(cmd->full_command[i], 0)
{

}

scan_envp(cmd, id_len)
{

}
