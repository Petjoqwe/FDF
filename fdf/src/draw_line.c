/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_line(t_line *line, t_point p1, t_point p2)
{
	line->x0 = p1.x;
	line->y0 = p1.y;
	line->x1 = p2.x;
	line->y1 = p2.y;
	line->dx = abs(line->x1 - line->x0);
	line->dy = abs(line->y1 - line->y0);
	if (line->x0 < line->x1)
		line->sx = 1;
	else
		line->sx = -1;
	if (line->y0 < line->y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx - line->dy;
}

void	plot_pixel(mlx_image_t *img, int x, int y, int color)
{
	if (is_in_bounds(x, y))
		mlx_put_pixel(img, x, y, color << 8 | 0xFF);
}

void	draw_line_loop(mlx_image_t *img, t_line *line, t_point p1, t_point p2)
{
	double	percent;
	int		color;
	int		total_distance;
	int		current_distance;

	total_distance = sqrt(pow(line->x1 - line->x0, 2)
			+ pow(line->y1 - line->y0, 2));
	while (1)
	{
		current_distance = sqrt(pow(line->x0 - p1.x, 2)
				+ pow(line->y0 - p1.y, 2));
		percent = (double)current_distance / total_distance;
		color = get_gradient(p1.color, p2.color, percent);
		plot_pixel(img, line->x0, line->y0, color);
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		line->e2 = 2 * line->err;
		if (line->e2 > -line->dy)
		{
			line->err -= line->dy;
			line->x0 += line->sx;
		}
		if (line->e2 < line->dx)
		{
			line->err += line->dx;
			line->y0 += line->sy;
		}
	}
}

void	draw_line(mlx_image_t *img, t_point p1, t_point p2)
{
	t_line	line;

	init_line(&line, p1, p2);
	draw_line_loop(img, &line, p1, p2);
}
