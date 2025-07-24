/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paguiler <paguiler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by paguiler          #+#    #+#             */
/*   Updated: 2025/07/23 02:32:25 by paguiler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/render.h"
#include "../includes/utils.h"
#include "../includes/transform.h"

void	clear_image(mlx_image_t *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < (int)img->height)
	{
		x = 0;
		while (x < (int)img->width)
		{
			mlx_put_pixel(img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

static int	get_height_color(int z, int z_min, int z_max)
{
	float	ratio;
	int		red;
	int		green;
	int		blue;

	if (z_max == z_min)
		return (0xFFFFFF);
	ratio = (float)(z - z_min) / (z_max - z_min);
	red = (int)(255 * ratio);
	green = (int)(255 * (1 - ratio));
	blue = 128;
	return ((red << 16) | (green << 8) | blue);
}

static t_point	project_point(t_point p, t_cam *cam)
{
	t_point	projected;
	t_point	rotated;
	float	x;
	float	y;
	float	z;

	rotated = apply_rotation(p, cam);
	x = rotated.x - cam->x_offset;
	y = rotated.y - cam->y_offset;
	z = rotated.z;
	projected.x = (x - y) * cos(cam->angle_x) * cam->zoom + WIN_WIDTH / 2;
	projected.y = (x + y) * sin(cam->angle_y) * cam->zoom - z * cam->zoom
		+ WIN_HEIGHT / 2;
	projected.z = rotated.z;
	projected.color = rotated.color;
	return (projected);
}

static void	draw_line_bresenham(mlx_image_t *img, t_point p1, t_point p2)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(p2.x - p1.x);
	dy = abs(p2.y - p1.y);
	sx = (p1.x < p2.x) ? 1 : -1;
	sy = (p1.y < p2.y) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		if (p1.x >= 0 && p1.x < (int)img->width && p1.y >= 0
			&& p1.y < (int)img->height)
			mlx_put_pixel(img, p1.x, p1.y, p1.color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			p1.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			p1.y += sy;
		}
	}
}

void	draw_line(mlx_image_t *img, t_point p1, t_point p2, t_cam *cam)
{
	t_point	proj1;
	t_point	proj2;

	proj1 = project_point(p1, cam);
	proj2 = project_point(p2, cam);
	draw_line_bresenham(img, proj1, proj2);
}

void	render_map(t_fdf *fdf)
{
	int	y;
	int	x;
	t_point	p1;
	t_point	p2;

	clear_image(fdf->img);
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			p1 = fdf->map->points[y][x];
			if (p1.color == 0xFFFFFF)
				p1.color = get_height_color(p1.z, fdf->map->z_min, fdf->map->z_max);
			if (x < fdf->map->width - 1)
			{
				p2 = fdf->map->points[y][x + 1];
				if (p2.color == 0xFFFFFF)
					p2.color = get_height_color(p2.z, fdf->map->z_min, fdf->map->z_max);
				draw_line(fdf->img, p1, p2, fdf->cam);
			}
			if (y < fdf->map->height - 1)
			{
				p2 = fdf->map->points[y + 1][x];
				if (p2.color == 0xFFFFFF)
					p2.color = get_height_color(p2.z, fdf->map->z_min, fdf->map->z_max);
				draw_line(fdf->img, p1, p2, fdf->cam);
			}
			x++;
		}
		y++;
	}
} 