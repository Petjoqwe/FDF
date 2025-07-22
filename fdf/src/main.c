/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_exit(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	init_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, true);
	if (!fdf->mlx)
		error_exit("Failed to initialize MLX");
	fdf->img = mlx_new_image(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!fdf->img)
	{
		mlx_terminate(fdf->mlx);
		error_exit("Failed to create image");
	}
	if (mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) == -1)
	{
		mlx_delete_image(fdf->mlx, fdf->img);
		mlx_terminate(fdf->mlx);
		error_exit("Failed to put image to window");
	}
	fdf->cam = malloc(sizeof(t_cam));
	if (!fdf->cam)
		cleanup_and_exit(fdf, "Failed to allocate camera");
	init_camera(fdf->cam, fdf->map);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		error_exit("Usage: ./fdf <map_file>");
	ft_memset(&fdf, 0, sizeof(t_fdf));
	fdf.map = parse_map(argv[1]);
	if (!fdf.map)
		error_exit("Failed to parse map");
	init_fdf(&fdf);
	render(&fdf);
	mlx_key_hook(fdf.mlx, &key_hook, &fdf);
	mlx_close_hook(fdf.mlx, &close_hook, &fdf);
	mlx_loop(fdf.mlx);
	free_fdf(&fdf);
	return (0);
}
