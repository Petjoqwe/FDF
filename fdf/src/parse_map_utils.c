/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
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

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->points)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->points[i])
				free(map->points[i]);
			i++;
		}
		free(map->points);
	}
	free(map);
}

int	validate_map_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static void	parse_point(char *str, t_point *point, int x, int y)
{
	char	**parts;

	parts = ft_split(str, ',');
	if (!parts || !parts[0])
		error_exit("Invalid map format");
	point->x = x;
	point->y = y;
	point->z = ft_atoi(parts[0]);
	if (parts[1])
		point->color = get_color(parts[1]);
	else
		point->color = 0xFFFFFF;
	free_split(parts);
}

void	process_map_line(char *line, t_map *map, int y)
{
	char	**values;
	int		x;

	values = ft_split(line, ' ');
	if (!values)
		error_exit("Memory allocation failed");
	x = 0;
	while (values[x] && x < map->width)
	{
		parse_point(values[x], &map->points[y][x], x, y);
		if (map->points[y][x].z > map->max_z)
			map->max_z = map->points[y][x].z;
		if (map->points[y][x].z < map->min_z)
			map->min_z = map->points[y][x].z;
		x++;
	}
	free_split(values);
}
