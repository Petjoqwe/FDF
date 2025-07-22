/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 10:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/render.h"

static t_point	project_point(t_point p, t_fdf *fdf)
{
	t_point	proj;

	proj = p;
	proj.x *= fdf->zoom;
	proj.y *= fdf->zoom;
	proj.z *= fdf->zoom * fdf->z_scale;
	apply_isometric(&proj.x, &proj.y, proj.z);
	proj.x += fdf->x_offset;
	proj.y += fdf->y_offset;
	return (proj);
}

static void	draw_horizontal_lines(t_fdf *fdf)
{
	int		x;
	int		y;
	t_point	p1;
	t_point	p2;
	t_line	line;

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width - 1)
		{
			p1 = project_point(fdf->map->points[y][x], fdf);
			p2 = project_point(fdf->map->points[y][x + 1], fdf);
			line = (t_line){p1.x, p1.y, p2.x, p2.y, 0, 0, 0, 0, 0};
			draw_line(fdf->img, line, p1.color);
			x++;
		}
		y++;
	}
}

static void	draw_vertical_lines(t_fdf *fdf)
{
	int		x;
	int		y;
	t_point	p1;
	t_point	p2;
	t_line	line;

	x = 0;
	while (x < fdf->map->width)
	{
		y = 0;
		while (y < fdf->map->height - 1)
		{
			p1 = project_point(fdf->map->points[y][x], fdf);
			p2 = project_point(fdf->map->points[y + 1][x], fdf);
			line = (t_line){p1.x, p1.y, p2.x, p2.y, 0, 0, 0, 0, 0};
			draw_line(fdf->img, line, p1.color);
			y++;
		}
		x++;
	}
}

void	render_map(t_fdf *fdf)
{
	clear_image(fdf->img);
	draw_horizontal_lines(fdf);
	draw_vertical_lines(fdf);
}

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
