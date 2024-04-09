/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:31:31 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/09 14:18:37 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

size_t	get_len_arr(char **array)
{
	size_t	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i])
	{
		i++;
	}
	return (i);
}

int	ft_isspace(int c)
{
	//printf("enters ft_isspace");
	if (c == ' ' || (c >= 9 && c <= 13))
	{
		//printf("LE char est '%c' \n et la valeur retournee 1", c);
		return (1);
	}

	else
	{
		//printf("LE char est '%c' \n et la valeur retournee 0", c);
		return (0);
	}

}

/*
delete a str from a string array
pos : position of the first str to del
count : how many str to delete


*/
char	**del_str_from_array(char **array, int pos, int count)
{
	int	i;
	int	buff;

	//printf("enters del\n");
	i = 0;
	while (i++ < count)
	{
		buff = pos;
		free(array[buff]);
		while (array[++buff])
			array[buff - 1] = array[buff];
		array[buff - 1] = NULL;
	}
	return (array);
}

char	**add_str_to_arr(char **arr, char *str)
{
	char	**new;
	int		l;

	l = get_len_arr(arr);
	new = ft_calloc(l + 2, sizeof(char *));
	if (!new)
		return (NULL);
	new[l] = ft_strdup(str);
	l--;
	while (l >= 0)
	{
		new[l] = ft_strdup(arr[l]);
		l--;
	}
	free_char_array(arr);
	return (new);
}

// char **del_str_from_array(char **array, int pos, int count)
// {
// 	int	new_size;
// 	int	i;
// 	int	j;
// 	char	**temp;

// 	j = 0;
// 	i = 0;
// 	new_size = 0;
// 	new_size = get_len_arr(array) - count;
// 	temp = (char **)malloc((new_size + 1) * sizeof(char *));
// 	if (temp == NULL)
// 		return (NULL);
// 	while (array[i])
// 	{
// 		if (i < pos || i >= pos + count)
// 		{
// 			temp[j] = array[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	temp[j] = NULL;
// 	free(array);
// 	return (temp);
// }

void	print_err_msg(char *cmd, char *msg) //replace with below print_err_msg_lng if possible
{
	if (!msg)
		return ;
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

int print_err_msg_lng(char *cmd, char *msg, char *arg) //different -> compare all err msgs with bash
{
	//check arg, msg, cmd != NULL necessary?
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	if (msg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
	}
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putstr_fd("\n", 2);
	return (1);
}
