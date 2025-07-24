/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paguiler <paguiler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by paguiler          #+#    #+#             */
/*   Updated: 2025/07/22 19:23:17 by paguiler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/render.h"
#include "../includes/utils.h"

void	calculate_zoom(t_fdf *fdf)
{
	int	scale_x;
	int	scale_y;
	int	range_z;

	scale_x = WIN_WIDTH / (fdf->map->width + 1) / 2;
	scale_y = WIN_HEIGHT / (fdf->map->height + 1) / 2;
	fdf->cam->zoom = ft_max(5, ft_max(scale_x, scale_y));
	range_z = fdf->map->z_max - fdf->map->z_min;
	if (range_z > 50)
		fdf->cam->zoom = fdf->cam->zoom * 50 / range_z;
}

static void	draw_horizontal_lines(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	p2;

	if (x < fdf->map->width - 1)
	{
		project_point(&fdf->map->points[y][x], &p1, fdf);
		project_point(&fdf->map->points[y][x + 1], &p2, fdf);
		draw_line(fdf->img, p1, p2);
	}
}

static void	draw_vertical_lines(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	p2;

	if (y < fdf->map->height - 1)
	{
		project_point(&fdf->map->points[y][x], &p1, fdf);
		project_point(&fdf->map->points[y + 1][x], &p2, fdf);
		draw_line(fdf->img, p1, p2);
	}
}

void	render_map(t_fdf *fdf)
{
	int	x;
	int	y;

	clear_image(fdf->img);
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