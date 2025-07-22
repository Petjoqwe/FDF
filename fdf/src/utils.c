/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open file");
	return (fd);
}

char	**ft_split_whitespace(char *str)
{
	return (ft_split(str, ' '));
}

int	count_words(char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		str++;
	}
	return (count);
}

int	get_gradient(int start, int end, double percent)
{
	int	r;
	int	g;
	int	b;

	if (percent < 0)
		percent = 0;
	if (percent > 1)
		percent = 1;
	r = ((start >> 16) & 0xFF) + (((end >> 16) & 0xFF)
			- ((start >> 16) & 0xFF)) * percent;
	g = ((start >> 8) & 0xFF) + (((end >> 8) & 0xFF)
			- ((start >> 8) & 0xFF)) * percent;
	b = (start & 0xFF) + ((end & 0xFF) - (start & 0xFF)) * percent;
	return ((r << 16) | (g << 8) | b);
}
