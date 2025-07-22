/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <MLX42/MLX42.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WINDOW_WIDTH	1920
# define WINDOW_HEIGHT	1080
# define WINDOW_TITLE	"FDF - Wireframe Model"

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}	t_point;

typedef struct s_map
{
	t_point	**points;
	int		width;
	int		height;
	int		z_min;
	int		z_max;
}	t_map;

typedef struct s_cam
{
	int		x_offset;
	int		y_offset;
	double	zoom;
	double	z_scale;
	double	angle_x;
	double	angle_y;
	double	angle_z;
}	t_cam;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;
	t_cam		*cam;
}	t_fdf;

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_line;

/* Main */
void	error_exit(char *msg);
void	init_fdf(t_fdf *fdf);

/* Parse map */
t_map	*parse_map(char *filename);
void	read_map_dimensions(char *filename, t_map *map);
void	allocate_map(t_map *map);
void	fill_map(char *filename, t_map *map);

/* Parse utils */
int		get_color(char *str);
void	parse_point(char *str, t_point *point, int x, int y);
void	find_z_limits(t_map *map);
int		validate_line(char *line);

/* Render */
void	render(t_fdf *fdf);
void	draw_map(t_fdf *fdf);
void	clear_image(mlx_image_t *img);

/* Render utils */
void	init_camera(t_cam *cam, t_map *map);
t_point	project_point(t_point p, t_cam *cam);
int		is_in_bounds(int x, int y);

/* Draw line */
void	draw_line(mlx_image_t *img, t_point p1, t_point p2);
void	init_line(t_line *line, t_point p1, t_point p2);
void	plot_pixel(mlx_image_t *img, int x, int y, int color);

/* Projection */
void	apply_rotation(t_point *p, t_cam *cam);
void	apply_zoom(t_point *p, t_cam *cam);
void	apply_offset(t_point *p, t_cam *cam);

/* Events */
void	key_hook(mlx_key_data_t keydata, void *param);
void	close_hook(void *param);
void	handle_keys(mlx_key_data_t keydata, t_fdf *fdf);

/* Utils */
int		open_file(char *filename);
char	**ft_split_whitespace(char *str);
int		count_words(char *str);
int		get_gradient(int start, int end, double percent);

/* Free utils */
void	free_map(t_map *map);
void	free_split(char **split);
void	free_fdf(t_fdf *fdf);
void	cleanup_and_exit(t_fdf *fdf, char *msg);

#endif
