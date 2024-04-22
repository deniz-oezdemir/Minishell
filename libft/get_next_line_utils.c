/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:40:56 by ecarlier          #+#    #+#             */
/*   Updated: 2023/12/04 13:47:59 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	line = fill_line(fd, leftover);
	leftover = set_left(line);
	if (line == NULL)
		return (NULL);
	return (line);
}

char	*fill_line(int fd, char *line)
{
	static char	buffer[BUFFER_SIZE +1];
	int			bytes_read;

	if (fd < 0)
		return (NULL);
	while (!ft_strchr(line, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read == -1)
		{
			free(line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		line = ft_strjoin(line, buffer);
	}
	return (line);
}

char	*set_left(char *line)
{
	char	*next;
	char	*surplus;

	next = ft_strchr(line, '\n');
	if (next++ == NULL)
		return (NULL);
	surplus = ft_strdup(next);
	if (!surplus)
		return (NULL);
	*next = '\0';
	return (surplus);
}
/*
char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	if (!s)
		return (NULL);
	ptr = (char *)s;
	while (*ptr != '\0')
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr++;
	}
	return (NULL);
}*/
