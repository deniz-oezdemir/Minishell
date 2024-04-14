/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:25:27 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/14 20:12:03 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_heredoc(t_prompt *prompt, t_cmddat *cmd, int i)
{
	char	*lim;
	int		j;

	lim = prompt->commands[i + 1]; //is is position of <<
	j = 0;
	while(ft_isalnum(lim[j]))
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
	char *content;
	char *line;

	content = NULL;
	line = NULL;
	exitstatus = 0; //why?
	while (1)
	{
		signals_interactive();
		line = readline("> ");
		signals_non_interactive();
		if (!line) //if e.g. Ctrl+D
		{
			print_err_msg("warning", "here-document delimited by end-of-file");
			break ;
		}
		if (!ft_strncmp(line, lim, ft_strlen(line)) && ft_strlen(line) == ft_strlen(lim)) //different: left out exitstatus as exitstatus can not be 1 here anyways?
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

	if (exitstatus)
	{
		free(content);
		return (0);
	}
	//check for meta chars / expand env vars -> @Leo
	if (!pipe(pip))
	{
		ft_putstr_fd(content, pip[1]);
		free(content);
		close(pip[1]);
		return(pip[0]);
	}
	free(content);
	return (0);
}
