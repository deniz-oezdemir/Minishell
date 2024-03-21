/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:38:15 by denizozd          #+#    #+#             */
/*   Updated: 2024/03/18 17:51:58 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_ms(int exitstatus, t_prompt *prompt)
{
	//free_all(prompt); //write
	exit(exitstatus);
}
