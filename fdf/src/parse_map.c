/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	read_map_dimensions(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		width;

	fd = open_file(filename);
	map->height = 0;
	map->width = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!validate_line(line))
		{
			free(line);
			close(fd);
			error_exit("Invalid map format");
		}
		width = count_words(line);
		if (map->width == 0)
			map->width = width;
		else if (map->width != width)
		{
			free(line);
			close(fd);
			error_exit("Map lines must have same width");
		}
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	allocate_map(t_map *map)
{
	int	y;

	map->points = malloc(sizeof(t_point *) * map->height);
	if (!map->points)
		error_exit("Failed to allocate map");
	y = 0;
	while (y < map->height)
	{
		map->points[y] = malloc(sizeof(t_point) * map->width);
		if (!map->points[y])
		{
			while (--y >= 0)
				free(map->points[y]);
			free(map->points);
			error_exit("Failed to allocate map row");
		}
		y++;
	}
}

void	fill_map(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	char	**split;
	int		y;
	int		x;

	fd = open_file(filename);
	y = 0;
	line = get_next_line(fd);
	while (line && y < map->height)
	{
		split = ft_split_whitespace(line);
		if (!split)
		{
			free(line);
			close(fd);
			error_exit("Failed to split line");
		}
		x = 0;
		while (x < map->width && split[x])
		{
			parse_point(split[x], &map->points[y][x], x, y);
			x++;
		}
		free_split(split);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	close(fd);
}

t_map	*parse_map(char *filename)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		error_exit("Failed to allocate map structure");
	read_map_dimensions(filename, map);
	if (map->width == 0 || map->height == 0)
	{
		free(map);
		error_exit("Empty map");
	}
	allocate_map(map);
	fill_map(filename, map);
	find_z_limits(map);
	return (map);
}
