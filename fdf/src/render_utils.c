/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 10:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/render.h"
#include "../include/utils.h"

void	apply_isometric(int *x, int *y, int z)
{
	int	temp_x;
	int	temp_y;

	temp_x = *x;
	temp_y = *y;
	*x = (temp_x - temp_y) * cos(0.523599);
	*y = (temp_x + temp_y) * sin(0.523599) - z;
}

static void	init_line(t_line *line)
{
	line->dx = ft_abs(line->x1 - line->x0);
	line->dy = -ft_abs(line->y1 - line->y0);
	if (line->x0 < line->x1)
		line->sx = 1;
	else
		line->sx = -1;
	if (line->y0 < line->y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx + line->dy;
}

static int	is_valid_pixel(int x, int y, mlx_image_t *img)
{
	if (x < 0 || y < 0)
		return (0);
	if ((uint32_t)x >= img->width || (uint32_t)y >= img->height)
		return (0);
	return (1);
}

void	draw_line(mlx_image_t *img, t_line line, int color)
{
	int	e2;

	init_line(&line);
	while (1)
	{
		if (is_valid_pixel(line.x0, line.y0, img))
			mlx_put_pixel(img, line.x0, line.y0, color << 8 | 0xFF);
		if (line.x0 == line.x1 && line.y0 == line.y1)
			break ;
		e2 = 2 * line.err;
		if (e2 >= line.dy)
		{
			line.err += line.dy;
			line.x0 += line.sx;
		}
		if (e2 <= line.dx)
		{
			line.err += line.dx;
			line.y0 += line.sy;
		}
	}
}
