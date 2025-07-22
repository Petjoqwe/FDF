/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 10:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/map.h"
#include "../include/render.h"
#include "../include/events.h"
#include "../include/utils.h"

static void	init_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (!fdf->mlx)
		error_exit("Failed to initialize MLX");
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->img)
		error_exit("Failed to create image");
	if (mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) == -1)
		error_exit("Failed to display image");
	fdf->zoom = 20;
	fdf->x_offset = WIDTH / 2;
	fdf->y_offset = HEIGHT / 2;
	fdf->z_scale = 0.1;
}

static void	cleanup_fdf(t_fdf *fdf)
{
	if (fdf->img)
		mlx_delete_image(fdf->mlx, fdf->img);
	if (fdf->mlx)
		mlx_terminate(fdf->mlx);
	if (fdf->map)
		free_map(fdf->map);
}

static void	check_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		error_exit("Usage: ./fdf <map.fdf>");
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".fdf", 4) != 0)
		error_exit("File must have .fdf extension");
	if (!validate_map_file(argv[1]))
		error_exit("Invalid map file");
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	ft_memset(&fdf, 0, sizeof(t_fdf));
	check_args(argc, argv);
	fdf.map = parse_map(argv[1]);
	if (!fdf.map)
		error_exit("Failed to parse map");
	init_fdf(&fdf);
	render_map(&fdf);
	setup_hooks(&fdf);
	mlx_loop(fdf.mlx);
	cleanup_fdf(&fdf);
	return (0);
}
