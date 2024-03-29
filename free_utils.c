/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:32:34 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/29 15:40:35 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_char_array(char **array)
{
	if (array == NULL)
		return ;
	while (*array != NULL)
	{
		free(*array);
		array++;
	}
	free(array);
}
