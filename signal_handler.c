/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:55:10 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/24 21:05:59 by ecarlier         ###   ########.fr       */
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
		//g_exitstatus = 131;
		ft_printf("Quit (core dumped)");
	}
	write(1, "\n", STDERR_FILENO);
	rl_on_new_line();
}

/* Ctrl+c*/
void	handle_sig_int(int n)
{
	//(void)n;
	if (n == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", STDERR_FILENO);
		rl_redisplay();
	}

	// if (n == SIGINT)
	// 	g_exitstatus = 130;
}

void	sig_handler_here_doc(int num)
{

// 	 if (num != SIGINT)
// 	 	return ;
// 	//ft_putendl_fd("", STDOUT_FILENO);
// 	rl_on_new_line();
// 	ioctl(STDIN_FILENO, TIOCSTI, "\n");
// 	// rl_replace_line("", 0);
// 	// rl_redisplay();

	if (num == SIGINT)
	{
		g_exitstatus = 1;
	}
		//write(1, "\n", STDERR_FILENO);
	//rl_on_new_line();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_redisplay();
	rl_replace_line("", 0);

}


