/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paguiler <paguiler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:02:51 by paguiler          #+#    #+#             */
/*   Updated: 2025/05/24 21:53:37 by paguiler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>     // open
#include <stdio.h>     // printf, perror
#include <unistd.h>    // close
#include <stdlib.h>    // free
#include "get_next_line.h" // tu función get_next_line

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc < 2)
	{
		printf("Usage: %s <file>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
