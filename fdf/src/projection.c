/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_point *p, double angle)
{
	int	prev_y;
	int	prev_z;

	prev_y = p->y;
	prev_z = p->z;
	p->y = prev_y * cos(angle) - prev_z * sin(angle);
	p->z = prev_y * sin(angle) + prev_z * cos(angle);
}

void	rotate_y(t_point *p, double angle)
{
	int	prev_x;
	int	prev_z;

	prev_x = p->x;
	prev_z = p->z;
	p->x = prev_x * cos(angle) + prev_z * sin(angle);
	p->z = -prev_x * sin(angle) + prev_z * cos(angle);
}

void	rotate_z(t_point *p, double angle)
{
	int	prev_x;
	int	prev_y;

	prev_x = p->x;
	prev_y = p->y;
	p->x = prev_x * cos(angle) - prev_y * sin(angle);
	p->y = prev_x * sin(angle) + prev_y * cos(angle);
}

void	apply_rotation(t_point *p, t_cam *cam)
{
	rotate_x(p, cam->angle_x);
	rotate_y(p, cam->angle_y);
	rotate_z(p, cam->angle_z);
}

void	apply_zoom(t_point *p, t_cam *cam)
{
	p->x *= cam->zoom;
	p->y *= cam->zoom;
}

void	apply_offset(t_point *p, t_cam *cam)
{
	p->x += cam->x_offset;
	p->y += cam->y_offset;
}
