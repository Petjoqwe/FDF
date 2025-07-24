/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paguiler <paguiler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by paguiler          #+#    #+#             */
/*   Updated: 2025/07/22 20:19:01 by paguiler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_join(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (stash);
	buffer[bytes_read] = '\0';
	temp = ft_strjoin(stash, buffer);
	if (stash)
		free(stash);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*newline;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!stash || !ft_strchr(stash, '\n'))
	{
		stash = read_and_join(fd, stash);
		if (!stash)
			return (NULL);
		if (ft_strlen(stash) == 0)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
	}
	newline = ft_strchr(stash, '\n');
	if (newline)
	{
		line = ft_substr(stash, 0, newline - stash + 1);
		temp = ft_strdup(newline + 1);
		free(stash);
		stash = temp;
	}
	else
	{
		line = ft_strdup(stash);
		free(stash);
		stash = NULL;
	}
	return (line);
}
