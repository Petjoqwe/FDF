/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paguiler <paguiler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by paguiler          #+#    #+#             */
/*   Updated: 2025/07/23 02:32:12 by paguiler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/events.h"
#include "../includes/render.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(fdf->mlx);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		fdf->cam->y_offset -= 20;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		fdf->cam->y_offset += 20;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		fdf->cam->x_offset -= 20;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		fdf->cam->x_offset += 20;
	if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
		fdf->cam->zoom *= 1.2;
	if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
		fdf->cam->zoom /= 1.2;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		fdf->cam->angle_x += 0.1;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		fdf->cam->angle_x -= 0.1;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		fdf->cam->angle_y += 0.1;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		fdf->cam->angle_y -= 0.1;
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		fdf->cam->rot_z += 0.1;
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		fdf->cam->rot_z -= 0.1;
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		fdf->cam->zoom = 30.0;
		fdf->cam->angle_x = 0.785398;
		fdf->cam->angle_y = 0.785398;
		fdf->cam->x_offset = fdf->map->width / 2;
		fdf->cam->y_offset = fdf->map->height / 2;
		fdf->cam->rot_x = 0.0;
		fdf->cam->rot_y = 0.0;
		fdf->cam->rot_z = 0.0;
	}
	render_map(fdf);
}

void	close_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	mlx_close_window(fdf->mlx);
}

void	setup_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx, key_hook, fdf);
	mlx_close_hook(fdf->mlx, close_hook, fdf);
} 