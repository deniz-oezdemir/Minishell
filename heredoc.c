/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:25:27 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/22 16:23:22 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_heredoc(t_prompt *prompt, t_cmddat *cmd, int i)
{
	char	*lim;
	size_t	j;

	lim = prompt->commands[i + 1];
	j = 0;
	while (ft_isalnum(lim[j]))
		j++;
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
	signals_here_doc();
	while (1)
	{

		//signals_interactive();
		line = readline("> ");
		collect_grbg(prompt, line);

		//signals_non_interactive();

		if (!line)
		{
			print_err_msg("warning", "here-document delimited by end-of-file");
			break ;
		}
		if (!ft_strncmp(line, lim, ft_strlen(line)) && ft_strlen(line) == ft_strlen(lim)) //different: left out prompt->prompt->prompt->prompt->prompt->exitstatus as prompt->exitstatus can not be 1 here anyways?
			break ;
		line = expand_var(prompt, line, prompt->envp);
		content = add_to_str(prompt, &content, line);
		content = add_to_str(prompt, &content, "\n");
	}
	signals_non_interactive();
	return (pipe_heredoc(content));
}

int	pipe_heredoc(char *content)
{
	int	pip[2];

	if (exitstatus) //@deniz why?
		return (0);
	if (!pipe(pip))
	{

		ft_putstr_fd(content, pip[1]);
		close(pip[1]);
		return (pip[0]);
	}
	return (0);
}
