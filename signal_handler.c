/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:55:10 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/22 14:36:14 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_interactive(void)
{
	signal(SIGINT, handle_sig_int);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_non_interactive(void)
{
	signal(SIGINT, handle_sig_quit);
	signal(SIGQUIT, handle_sig_quit);
}

/*
 Ctrl+\
 131
*/
void	handle_sig_quit(int n)
{
	if (n == SIGQUIT)
	{
		//exitstatus = 131;
		ft_printf("Quit (core dumped)");
	}
	write(1, "\n", STDERR_FILENO);
	rl_on_new_line();
}

/* Ctrl+c*/
void	handle_sig_int(int n)
{
	(void)n;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", STDERR_FILENO);
	rl_redisplay();
	// if (n == SIGINT)
	// 	exitstatus = 130;
}

// void	sig_handler_here_doc(int num)
// {
// 	if (num == SIGINT)
// 	{
// 		exitstatus = 1;
// 		write(1, "\n", STDERR_FILENO);
// 		//ioctl(STDIN_FILENO, TIOCSTI, "\n");
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 	}
// }
// void	sig_handler_after_rl(int num)
// {
// 	if (num == SIGINT)
// 		exitstatus = 130;
// }
// void	sig_handler_rl(int num)
// {
// 	if (num == SIGINT)
// 	{
// 		exitstatus = 1;
// 		write(1, "\n", STDERR_FILENO);
// 		//ioctl(STDIN_FILENO, TIOCSTI, "\n");
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 	}
// }
