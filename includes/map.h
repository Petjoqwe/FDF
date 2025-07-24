/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paguiler <paguiler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by paguiler          #+#    #+#             */
/*   Updated: 2025/07/22 19:20:43 by paguiler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "fdf.h"
# include "../libft/libft.h"

t_map	*parse_map(char *filename);
void	read_dimensions(int fd, t_map *map);
void	allocate_map(t_map *map);
void	parse_points(int fd, t_map *map);
void	free_map(t_map *map);

#endif 