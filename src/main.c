/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paguiler <paguiler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by paguiler          #+#    #+#             */
/*   Updated: 2025/07/23 02:31:50 by paguiler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/map.h"
#include "../includes/render.h"
#include "../includes/events.h"
#include "../includes/utils.h"

static void	center_map(t_fdf *fdf)
{
	int	center_x;
	int	center_y;

	center_x = fdf->map->width / 2;
	center_y = fdf->map->height / 2;
	fdf->cam->x_offset = center_x;
	fdf->cam->y_offset = center_y;
}

static t_cam	*init_camera(void)
{
	t_cam	*cam;

	cam = malloc(sizeof(t_cam));
	if (!cam)
		error_exit("Error: Memory allocation failed");
	cam->zoom = 30.0;
	cam->x_offset = 0;
	cam->y_offset = 0;
	cam->angle_x = 0.785398; // 45 grados en radianes
	cam->angle_y = 0.785398; // 45 grados en radianes
	cam->rot_x = 0.0;
	cam->rot_y = 0.0;
	cam->rot_z = 0.0;
	return (cam);
}

static t_fdf	*init_fdf(char *filename)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		error_exit("Error: Memory allocation failed");
	fdf->map = parse_map(filename);
	fdf->cam = init_camera();
	center_map(fdf);
	return (fdf);
}

static void	init_mlx(t_fdf *fdf)
{
	printf("Initializing MLX42...\n");
	fdf->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, TITLE, true);
	if (!fdf->mlx)
	{
		printf("Error: MLX initialization failed\n");
		error_exit("Error: MLX initialization failed");
	}
	printf("MLX42 initialized successfully\n");
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img)
	{
		printf("Error: Image creation failed\n");
		error_exit("Error: Image creation failed");
	}
	printf("Image created successfully\n");
	mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
	printf("Image added to window\n");
}

static void	cleanup_fdf(t_fdf *fdf)
{
	if (fdf)
	{
		if (fdf->map)
			free_map(fdf->map);
		if (fdf->cam)
			free(fdf->cam);
		free(fdf);
	}
}

static void	run_fdf(t_fdf *fdf)
{
	printf("Setting up hooks...\n");
	setup_hooks(fdf);
	printf("Rendering map...\n");
	render_map(fdf);
	printf("Starting MLX loop...\n");
	mlx_loop(fdf->mlx);
	printf("MLX loop ended\n");
	mlx_terminate(fdf->mlx);
	printf("MLX terminated\n");
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
	{
		printf("Usage: ./fdf <map.fdf>\n");
		return (1);
	}
	fdf = init_fdf(argv[1]);
	init_mlx(fdf);
	run_fdf(fdf);
	cleanup_fdf(fdf);
	return (0);
} 