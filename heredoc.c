/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:25:27 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/24 13:26:35 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_heredoc(t_prompt *prompt, t_cmddat *cmd, int i)
{
	char	*lim;
	size_t	j;

	lim = cmd->full_command[i + 1]; //leo changed this so it's from the right command
	//printf("lim : %s\n", lim);
	j = 0;

	while (ft_isalnum(lim[j]))
		j++;
	//printf("j : %zu \n", j);
	if (j != ft_strlen(lim))
	{
		ft_putstr_fd("minishell: input error: delimiter must contain only alphanumeric characters\n", 2);
		prompt->stop = 1;
		return ;
	}
	cmd->infile = get_heredoc(prompt, lim);
	if (exitstatus == 1)
		prompt->stop = 1; //why?
}

int	get_heredoc(t_prompt *prompt, char *lim)
{
	char	*content;
	char	*line;

	content = NULL;
	line = NULL;
	exitstatus = 0; //@deniz why?

	while (1)
	{
		//signals_here_doc(); //does not work
		signals_interactive();
		line = readline("> ");
		collect_grbg(prompt, line);
		signals_non_interactive();
		if (!line)
		{
			print_err_msg("warning", "here-document delimited by end-of-file");
			break ;
		}
		if (!ft_strncmp(line, lim, ft_strlen(line)) && ft_strlen(line) == ft_strlen(lim)) //different: left out prompt->prompt->prompt->prompt->prompt->exitstatus as prompt->exitstatus can not be 1 here anyways?
			break ;
		line = expand_var(prompt, line, prompt->envp, 0);
		//line = expand_var(prompt, line, prompt->envp);
		content = add_to_str(prompt, &content, line);
		content = add_to_str(prompt, &content, "\n");
	}
	return (pipe_heredoc(content));
}

int	pipe_heredoc(char *content)
{
	int	pip[2];

	if (exitstatus)
	{
		//printf("pipe\n");
		return (0); //@deniz why?
	}


	if (!pipe(pip))
	{
		ft_putstr_fd(content, pip[1]);
		close(pip[1]);
		return (pip[0]);
	}
	return (0);
}
