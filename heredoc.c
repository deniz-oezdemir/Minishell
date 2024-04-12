/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:25:27 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/12 14:09:38 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_heredoc(t_prompt *prompt, t_cmddat *cmd, int i)
{
	char	*lim;

	lim = prompt->commands[i + 1]; //is is position of <<
	cmd->infile = get_heredoc(prompt, lim);
}

int	get_heredoc(t_prompt *prompt, char *lim)
{
	char *content;
	char *line;

	content = NULL;
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, lim, ft_strlen(line)) && ft_strlen(line) == ft_strlen(lim))
			break ;
		content = add_to_str(&content, line);
		content = add_to_str(&content, "\n");
		free(line);
	}
	return (pipe_heredoc(prompt, content));
}

int	pipe_heredoc(t_prompt *prompt, char *content)
{
	int pip[2];
	int i;

	if (!pipe(pip))
	{
		ft_putstr_fd(content, pip[1]);
		//write(pip[1], content, ft_strlen(content)); //replaced with above putstr
		free(content);
		close(pip[1]);
		return(pip[0]);
	}
	free(content);
	return (0);
}
