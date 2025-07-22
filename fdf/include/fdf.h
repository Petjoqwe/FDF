/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 10:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <MLX42/MLX42.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1080
# define TITLE "FDF - Wireframe Model"

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
	int		max_z;
	int		min_z;
}	t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;
	double		zoom;
	double		x_offset;
	double		y_offset;
	double		z_scale;
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
}	t_line;

#endif
