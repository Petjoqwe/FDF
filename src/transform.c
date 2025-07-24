/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paguiler <paguiler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by paguiler          #+#    #+#             */
/*   Updated: 2025/07/23 02:31:12 by paguiler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/transform.h"

static t_point	rotate_x(t_point p, float angle)
{
	t_point	rotated;
	float	cos_a;
	float	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	rotated.x = p.x;
	rotated.y = p.y * cos_a - p.z * sin_a;
	rotated.z = p.y * sin_a + p.z * cos_a;
	rotated.color = p.color;
	return (rotated);
}

static t_point	rotate_y(t_point p, float angle)
{
	t_point	rotated;
	float	cos_a;
	float	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	rotated.x = p.x * cos_a + p.z * sin_a;
	rotated.y = p.y;
	rotated.z = -p.x * sin_a + p.z * cos_a;
	rotated.color = p.color;
	return (rotated);
}

static t_point	rotate_z(t_point p, float angle)
{
	t_point	rotated;
	float	cos_a;
	float	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	rotated.x = p.x * cos_a - p.y * sin_a;
	rotated.y = p.x * sin_a + p.y * cos_a;
	rotated.z = p.z;
	rotated.color = p.color;
	return (rotated);
}

t_point	apply_rotation(t_point p, t_cam *cam)
{
	t_point	rotated;

	rotated = rotate_x(p, cam->rot_x);
	rotated = rotate_y(rotated, cam->rot_y);
	rotated = rotate_z(rotated, cam->rot_z);
	return (rotated);
} 