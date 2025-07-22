/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_movement(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_UP)
		fdf->cam->y_offset -= 10;
	else if (keydata.key == MLX_KEY_DOWN)
		fdf->cam->y_offset += 10;
	else if (keydata.key == MLX_KEY_LEFT)
		fdf->cam->x_offset -= 10;
	else if (keydata.key == MLX_KEY_RIGHT)
		fdf->cam->x_offset += 10;
}

void	handle_zoom(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_EQUAL || keydata.key == MLX_KEY_KP_ADD)
		fdf->cam->zoom *= 1.1;
	else if (keydata.key == MLX_KEY_MINUS || keydata.key == MLX_KEY_KP_SUBTRACT)
		fdf->cam->zoom *= 0.9;
}

void	handle_rotation(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_W)
		fdf->cam->angle_x += 0.05;
	else if (keydata.key == MLX_KEY_S)
		fdf->cam->angle_x -= 0.05;
	else if (keydata.key == MLX_KEY_A)
		fdf->cam->angle_y -= 0.05;
	else if (keydata.key == MLX_KEY_D)
		fdf->cam->angle_y += 0.05;
	else if (keydata.key == MLX_KEY_Q)
		fdf->cam->angle_z -= 0.05;
	else if (keydata.key == MLX_KEY_E)
		fdf->cam->angle_z += 0.05;
}

void	handle_keys(mlx_key_data_t keydata, t_fdf *fdf)
{
	handle_movement(keydata, fdf);
	handle_zoom(keydata, fdf);
	handle_rotation(keydata, fdf);
	if (keydata.key == MLX_KEY_R)
		init_camera(fdf->cam, fdf->map);
	render(fdf);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(fdf->mlx);
	else
		handle_keys(keydata, fdf);
}

void	close_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	mlx_close_window(fdf->mlx);
}
