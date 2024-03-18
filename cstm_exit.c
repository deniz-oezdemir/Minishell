/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:16:10 by denizozd          #+#    #+#             */
/*   Updated: 2024/03/18 17:40:17 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_digits(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (ft_strlen(s) == i)
		return (1);
	return (0);
}

int	cstm_exit(t_cmmnds *cmd_data)
{
	int	exitstatus;

	exitstatus = 0;

	if (get_len_arr(cmd_data->full_command) >= 3 && is_only_digits(cmd_data->full_command[1])) //why is_only_digits? //test this case at the end
	{
		print_err_msg("exit", "too many arguments"); //check shells error messages
		return (1);
	}
	ft_putstr_fd("ms: exit\n", cmd_data->outfile); //test
	if (get_len_arr(cmd_data->full_command) >= 2 && !is_only_digits(cmd_data->full_command[1]))
	{
		ft_putstr_fd("exit: ", 2); //different //check shells error messages
		ft_putstr_fd(cmd_data->full_command[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2); //check shells error messages
	}
	if (cmd_data->full_command[1])
		exitstatus = ft_atoi(cmd_data->full_command[1]);
	exit_ms(exitstatus, cmd_data->prompt); //test
	return (0);
}
