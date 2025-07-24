/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paguiler <paguiler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by paguiler          #+#    #+#             */
/*   Updated: 2025/07/22 21:34:05 by paguiler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map.h"
#include "../includes/utils.h"

static char	*read_line_simple(int fd)
{
	char	buffer[1024];
	char	*line;
	ssize_t	bytes_read;
	int		i;

	line = malloc(1024);
	if (!line)
		return (NULL);
	i = 0;
	while (i < 1023)
	{
		bytes_read = read(fd, &buffer[i], 1);
		if (bytes_read <= 0)
			break ;
		if (buffer[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	buffer[i] = '\0';
	ft_strcpy(line, buffer);
	return (line);
}

static void	process_line(char *line, t_map *map, int *width)
{
	char	**split;

	split = ft_split(line, ' ');
	*width = 0;
	while (split && split[*width])
		(*width)++;
	if (*width > 0)
	{
		if (map->width == 0)
			map->width = *width;
		else if (map->width != *width)
		{
			free_split(split);
			free(line);
			error_exit("Error: Invalid map (inconsistent width)");
		}
		map->height++;
	}
	free_split(split);
}

void	read_dimensions(int fd, t_map *map)
{
	char	*line;
	int		width;
	int		line_count;

	map->height = 0;
	map->width = 0;
	line_count = 0;
	line = read_line_simple(fd);
	while (line && line_count < 20)
	{
		process_line(line, map, &width);
		free(line);
		line_count++;
		line = read_line_simple(fd);
	}
	if (line)
		free(line);
}

void	allocate_map(t_map *map)
{
	int	y;

	map->points = malloc(sizeof(t_point *) * map->height);
	if (!map->points)
		error_exit("Error: Memory allocation failed");
	y = 0;
	while (y < map->height)
	{
		map->points[y] = malloc(sizeof(t_point) * map->width);
		if (!map->points[y])
		{
			while (--y >= 0)
				free(map->points[y]);
			free(map->points);
			error_exit("Error: Memory allocation failed");
		}
		y++;
	}
	map->z_min = 0;
	map->z_max = 0;
}

static void	parse_point(char *str, t_point *point, int x, int y)
{
	char	**parts;

	parts = ft_split(str, ',');
	if (!parts || !parts[0])
		error_exit("Error: Invalid map format");
	point->x = x;
	point->y = y;
	point->z = ft_atoi(parts[0]);
	if (parts[1])
		point->color = get_color_value(parts[1]);
	else
		point->color = 0xFFFFFF;
	free_split(parts);
}

static void	process_point_line(char *line, t_map *map, int y)
{
	char	**split;
	int		x;
	int		width;

	split = ft_split(line, ' ');
	width = 0;
	while (split && split[width])
		width++;
	if (width > 0)
	{
		x = 0;
		while (split && split[x] && x < map->width)
		{
			parse_point(split[x], &map->points[y][x], x, y);
			if (map->points[y][x].z < map->z_min)
				map->z_min = map->points[y][x].z;
			if (map->points[y][x].z > map->z_max)
				map->z_max = map->points[y][x].z;
			x++;
		}
	}
	free_split(split);
}

void	parse_points(int fd, t_map *map)
{
	char	*line;
	int		y;
	int		line_count;

	y = 0;
	line_count = 0;
	line = read_line_simple(fd);
	while (line && y < map->height && line_count < 20)
	{
		process_point_line(line, map, y);
		free(line);
		y++;
		line_count++;
		line = read_line_simple(fd);
	}
	if (line)
		free(line);
}

t_map	*parse_map(char *filename)
{
	t_map	*map;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error: Cannot open file");
	map = malloc(sizeof(t_map));
	if (!map)
	{
		close(fd);
		error_exit("Error: Memory allocation failed");
	}
	read_dimensions(fd, map);
	close(fd);
	if (map->width == 0 || map->height == 0)
	{
		free(map);
		error_exit("Error: Empty map");
	}
	allocate_map(map);
	fd = open(filename, O_RDONLY);
	parse_points(fd, map);
	close(fd);
	return (map);
} 