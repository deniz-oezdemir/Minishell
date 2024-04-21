/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:16:10 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/21 17:49:10 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_digits(char *s)
{
	size_t	i;

	i = 0;
	while (ft_isdigit(s[i])) //different
		i++;
	if (ft_strlen(s) == i)
		return (1);
	return (0);
}

int	cstm_exit(t_cmddat *cmd_data)
{
	exitstatus = 0;
	if (get_len_arr(cmd_data->full_command) >= 3 && is_only_digits(cmd_data->full_command[1]))
	{
		print_err_msg("exit", "too many arguments");
		return (1);
	}
	ft_putstr_fd("exit\n", cmd_data->outfile);
	if (cmd_data->full_command[1])
	{
		exitstatus = ft_atoi(cmd_data->full_command[1]);
		if (exitstatus < 0)
			exitstatus = 256 + exitstatus;
	}
	if (get_len_arr(cmd_data->full_command) >= 2 && !exitstatus)
	{
		ft_putstr_fd("ms: exit: ", 2);
		ft_putstr_fd(cmd_data->full_command[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exitstatus = 2;
	}
	exit_ms(exitstatus, cmd_data->prompt);
	return (0);
}
