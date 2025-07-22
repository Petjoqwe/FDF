/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 10:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/events.h"
#include "../include/render.h"

static void	handle_zoom(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
	{
		fdf->zoom *= 1.1;
		render_map(fdf);
	}
	else if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
	{
		fdf->zoom *= 0.9;
		render_map(fdf);
	}
}

static void	handle_translation(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		fdf->y_offset -= 10;
		render_map(fdf);
	}
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		fdf->y_offset += 10;
		render_map(fdf);
	}
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		fdf->x_offset -= 10;
		render_map(fdf);
	}
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		fdf->x_offset += 10;
		render_map(fdf);
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(fdf->mlx);
	handle_zoom(keydata, fdf);
	handle_translation(keydata, fdf);
}

void	close_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	mlx_close_window(fdf->mlx);
}

void	setup_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx, &key_hook, fdf);
	mlx_close_hook(fdf->mlx, &close_hook, fdf);
}
