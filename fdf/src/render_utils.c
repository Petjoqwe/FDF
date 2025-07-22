/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_camera(t_cam *cam, t_map *map)
{
	int	scale_x;
	int	scale_y;

	scale_x = WINDOW_WIDTH / (map->width + 10);
	scale_y = WINDOW_HEIGHT / (map->height + 10);
	if (scale_x < scale_y)
		cam->zoom = scale_x;
	else
		cam->zoom = scale_y;
	cam->x_offset = WINDOW_WIDTH / 2;
	cam->y_offset = WINDOW_HEIGHT / 2;
	cam->z_scale = 0.1;
	cam->angle_x = -0.5;
	cam->angle_y = 0.0;
	cam->angle_z = 0.785398;
}

t_point	project_point(t_point p, t_cam *cam)
{
	t_point	projected;

	projected = p;
	projected.x -= cam->zoom * p.x / 2;
	projected.y -= cam->zoom * p.y / 2;
	projected.z = p.z * cam->z_scale * cam->zoom;
	apply_rotation(&projected, cam);
	apply_zoom(&projected, cam);
	apply_offset(&projected, cam);
	projected.color = p.color;
	return (projected);
}

int	is_in_bounds(int x, int y)
{
	if (x < 0 || x >= WINDOW_WIDTH)
		return (0);
	if (y < 0 || y >= WINDOW_HEIGHT)
		return (0);
	return (1);
}
