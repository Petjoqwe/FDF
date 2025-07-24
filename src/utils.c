/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paguiler <paguiler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by paguiler          #+#    #+#             */
/*   Updated: 2025/07/22 19:23:57 by paguiler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"
#include "../libft/libft.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
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

int	get_color_value(char *str)
{
	int	color;
	int	i;

	if (!str || str[0] != '0' || str[1] != 'x')
		return (0xFFFFFF);
	color = 0;
	i = 2;
	while (str[i])
	{
		color = color * 16;
		if (str[i] >= '0' && str[i] <= '9')
			color += str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			color += str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			color += str[i] - 'A' + 10;
		else
			return (0xFFFFFF);
		i++;
	}
	return ((color << 8) | 0xFF);
}

void	error_exit(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
} 