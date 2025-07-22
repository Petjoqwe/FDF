/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 10:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_read_to_buffer(int fd, char *buffer)
{
	char	*tmp;
	int		bytes_read;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, tmp);
	}
	free(tmp);
	return (buffer);
}

static char	*ft_get_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_substr(buffer, 0, i + (buffer[i] == '\n'));
	return (line);
}

static char	*ft_new_buffer(char *buffer)
{
	int		i;
	char	*new_buffer;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_strdup(buffer + i + 1);
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read_to_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	buffer = ft_new_buffer(buffer);
	return (line);
}
