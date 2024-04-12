/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:25:27 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/12 12:18:04 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_heredoc(t_prompt *prompt, t_cmddat *cmd, int i)
{
	char	*lim;

	lim = prompt->commands[i + 2]; //@Leo: what's i?
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
	return (pipe_heredoc(prompt, content)); //@Deniz: CONTINUE writing pipe_heredoc
}

int	pipe_heredoc(t_prompt *prompt, char *content)
{
	int pip[2];
	int i;

	if (!pipe(pip))
	{
		write(pip[1], content, ft_strlen(content)); //replace with putstr
		free(content);
		close(pip[1]);
		return(pip[0]);
	}
	free(content);
	return (0);
}

/*need to use pipe and signals_interactive*

		signals_interactive();
		line = readline(HERE_DOC_PROMPT);
		signals_non_interactive();
		/
// */



/*COMPLETLY LOST*/
// void	get_here_doc(t_prompt *prompt, t_cmddat *cmd_struct, int i)
// {

// 	char *line;

// 	line = NULL;
// 	while (1)
// 	{
// 		signals_interactive();
// 		line = readline("> ");
// 		if (!line)
// 			print_err_msg("warning", "here-document delimited by end-of-file");


// 	}

// }



// void	start_here_doc(t_prompt *prompt, t_cmddat *cmd_strc, int i)
// {

// }
