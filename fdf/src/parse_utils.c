/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color(char *str)
{
	char	*comma;
	char	*color_str;
	int		color;

	comma = ft_strchr(str, ',');
	if (!comma)
		return (0xFFFFFF);
	color_str = comma + 1;
	if (color_str[0] == '0' && (color_str[1] == 'x' || color_str[1] == 'X'))
		color_str += 2;
	color = 0;
	while (*color_str)
	{
		color = color * 16;
		if (*color_str >= '0' && *color_str <= '9')
			color += *color_str - '0';
		else if (*color_str >= 'a' && *color_str <= 'f')
			color += *color_str - 'a' + 10;
		else if (*color_str >= 'A' && *color_str <= 'F')
			color += *color_str - 'A' + 10;
		else
			break ;
		color_str++;
	}
	return (color);
}

void	parse_point(char *str, t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
	point->z = ft_atoi(str);
	point->color = get_color(str);
}

void	find_z_limits(t_map *map)
{
	int	x;
	int	y;

	map->z_min = map->points[0][0].z;
	map->z_max = map->points[0][0].z;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->points[y][x].z < map->z_min)
				map->z_min = map->points[y][x].z;
			if (map->points[y][x].z > map->z_max)
				map->z_max = map->points[y][x].z;
			x++;
		}
		y++;
	}
}

int	validate_line(char *line)
{
	int	i;

	i = 0;
	if (!line || !line[0])
		return (0);
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\n' && line[i] != '-' && line[i] != '+'
			&& line[i] != ',' && line[i] != 'x' && line[i] != 'X'
			&& !(line[i] >= 'a' && line[i] <= 'f')
			&& !(line[i] >= 'A' && line[i] <= 'F'))
			return (0);
		i++;
	}
	return (1);
}
