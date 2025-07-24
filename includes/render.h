/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paguiler <paguiler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by paguiler          #+#    #+#             */
/*   Updated: 2025/07/22 21:34:30 by paguiler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "fdf.h"

void	clear_image(mlx_image_t *img);
void	draw_line(mlx_image_t *img, t_point p1, t_point p2, t_cam *cam);
void	render_map(t_fdf *fdf);

#endif 