/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paguiler <paguiler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by paguiler          #+#    #+#             */
/*   Updated: 2025/07/22 19:21:23 by paguiler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "fdf.h"

int		ft_abs(int n);
int		ft_max(int a, int b);
void	free_split(char **split);
int		get_color_value(char *str);
void	error_exit(char *msg);

#endif 