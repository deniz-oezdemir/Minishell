/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:16:10 by denizozd          #+#    #+#             */
/*   Updated: 2024/09/16 19:52:16 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_only_digits(char *s)
{
	size_t	i;

	i = 0;
	while (ft_isdigit(s[i]))
		i++;
	if (ft_strlen(s) == i)
		return (1);
	return (0);
}

int	cstm_exit(t_cmddat *cmd_data)
{
	g_exitstatus = 0;
	if (get_len_arr(cmd_data->full_cmd) >= 3
		&& is_only_digits(cmd_data->full_cmd[1]))
	{
		print_err_msg("exit", "too many arguments");
		return (1);
	}
	ft_putstr_fd("exit\n", cmd_data->outfile);
	if (cmd_data->full_cmd[1])
	{
		g_exitstatus = ft_atoi(cmd_data->full_cmd[1]);
		if (g_exitstatus < 0)
			g_exitstatus = 256 + g_exitstatus;
	}
	if (get_len_arr(cmd_data->full_cmd) >= 2 && !g_exitstatus)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd_data->full_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_exitstatus = 2;
	}
	exit_ms(g_exitstatus, cmd_data->prompt);
	return (0);
}
