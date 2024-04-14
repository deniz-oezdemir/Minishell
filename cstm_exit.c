/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:16:10 by denizozd          #+#    #+#             */
/*   Updated: 2024/04/14 20:04:20 by denizozd         ###   ########.fr       */
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
	int	exitstatus;

	exitstatus = 0;

	if (get_len_arr(cmd_data->full_command) >= 3 && is_only_digits(cmd_data->full_command[1]))
	{
		print_err_msg("exit", "too many arguments");
		return (1);
	}
	ft_putstr_fd("exit\n", cmd_data->outfile);
	if (get_len_arr(cmd_data->full_command) >= 2 && !is_only_digits(cmd_data->full_command[1]))
	{
		ft_putstr_fd("ms: exit: ", 2);
		ft_putstr_fd(cmd_data->full_command[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	if (cmd_data->full_command[1])
		exitstatus = ft_atoi(cmd_data->full_command[1]);
	exit_ms(exitstatus, cmd_data->prompt);
	return (0);
}
