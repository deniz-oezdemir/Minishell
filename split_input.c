/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:39:22 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/14 18:58:31 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*exemple input = "ls -l | grep 'file.txt'" */

char **split_input(char *str)
{
	while (*str)
	{
		if (*str == 32) //ft_isspace
			str++;
		else if (*str == "<" || *str == ">" || *str == "|" )

	}
}



ft_count_words(char *str)
{

}
