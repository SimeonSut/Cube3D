/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 21:12:57 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/26 15:17:59 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include <mlx.h>
# include "cub3d.h"
# include "libft.h"

int		key_config(int keycode, void *param);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_squar(void *img, int size, int color, int mode);
void	map_render(t_data *data);
void	map_d_render(t_data *data);

void	texture_init(t_data *data);
void	texture_mapping_x(t_data *data);
void	texture_mapping_y_draw(t_data *data, int x, int y);
int		mouse_rotate(int x, void *param);

#endif
