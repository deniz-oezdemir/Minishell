/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:55:10 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/05 17:38:13 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	sigint_handler(int signum)
// {
// 	printf("\n Signal SIGINT received\n");
// }


void	signals_interactive(void)
{
	signal(SIGINT, handle_sig_int);
	signal(SIGQUIT, SIG_IGN);
}

/*
 Ctrl+\
 131
*/
void	handle_sig_quit(int n)
{
	if (n == SIGQUIT)
	{
		exitstatus = 131; //131: termination by signal
	}
}

/* Ctrl+c*/
void	handle_sig_int(int n)
{
	if (n == SIGINT)
	{
		exitstatus = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", STDERR_FILENO);
		rl_redisplay();
	}
}

