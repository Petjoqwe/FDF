/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 10:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/utils.h"

void	error_exit(char *msg)
{
	ft_putendl_fd("Error", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	exit(1);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	get_color(char *str)
{
	int	color;

	if (!str || str[0] != '0' || str[1] != 'x')
		return (0xFFFFFF);
	color = 0;
	str += 2;
	while (*str)
	{
		color *= 16;
		if (*str >= '0' && *str <= '9')
			color += *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			color += *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			color += *str - 'A' + 10;
		str++;
	}
	return (color);
}
