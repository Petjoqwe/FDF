/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 10:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "fdf.h"

void	render_map(t_fdf *fdf);
void	draw_line(mlx_image_t *img, t_line line, int color);
void	apply_isometric(int *x, int *y, int z);
void	clear_image(mlx_image_t *img);

#endif
