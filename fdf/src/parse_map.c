/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 10:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/map.h"
#include "../include/utils.h"

static int	count_words(char *line)
{
	int		count;
	char	**words;

	words = ft_split(line, ' ');
	if (!words)
		return (0);
	count = 0;
	while (words[count])
		count++;
	free_split(words);
	return (count);
}

static void	get_map_dimensions(char *filename, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open file");
	map->height = 0;
	map->width = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (map->width == 0)
			map->width = count_words(line);
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (map->width == 0 || map->height == 0)
		error_exit("Empty map");
}

static void	allocate_map(t_map *map)
{
	int	i;

	map->points = (t_point **)malloc(sizeof(t_point *) * map->height);
	if (!map->points)
		error_exit("Memory allocation failed");
	i = 0;
	while (i < map->height)
	{
		map->points[i] = (t_point *)malloc(sizeof(t_point) * map->width);
		if (!map->points[i])
		{
			while (--i >= 0)
				free(map->points[i]);
			free(map->points);
			error_exit("Memory allocation failed");
		}
		i++;
	}
	map->max_z = 0;
	map->min_z = 0;
}

static void	fill_map(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open file");
	y = 0;
	line = get_next_line(fd);
	while (line && y < map->height)
	{
		process_map_line(line, map, y);
		free(line);
		y++;
		line = get_next_line(fd);
	}
	close(fd);
}

t_map	*parse_map(char *filename)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		error_exit("Memory allocation failed");
	get_map_dimensions(filename, map);
	allocate_map(map);
	fill_map(filename, map);
	return (map);
}
