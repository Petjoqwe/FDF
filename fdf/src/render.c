/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_image(mlx_image_t *img)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

void	draw_horizontal_lines(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	p2;

	if (x < fdf->map->width - 1)
	{
		p1 = project_point(fdf->map->points[y][x], fdf->cam);
		p2 = project_point(fdf->map->points[y][x + 1], fdf->cam);
		draw_line(fdf->img, p1, p2);
	}
}

void	draw_vertical_lines(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	p2;

	if (y < fdf->map->height - 1)
	{
		p1 = project_point(fdf->map->points[y][x], fdf->cam);
		p2 = project_point(fdf->map->points[y + 1][x], fdf->cam);
		draw_line(fdf->img, p1, p2);
	}
}

void	draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			draw_horizontal_lines(fdf, x, y);
			draw_vertical_lines(fdf, x, y);
			x++;
		}
		y++;
	}
}

void	render(t_fdf *fdf)
{
	clear_image(fdf->img);
	draw_map(fdf);
}
