/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 21:12:57 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/01 16:41:08 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include <mlx.h>
# include "cub3d.h"
# include "libft.h"

int		key_config(int keycode, void *param);
int		close_window(void *param);
double	sidewalk(t_data *data, double r, int keycode, int axis);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	delta_dist_calculation(t_data *data);
void	new_pos_cal(double *new_x, double *new_y, t_data *data, int key);

void	map_d_render(t_data *data);

int		texture_init(t_data	*data, t_texture *txt);
void	texture_mapping_x(t_data *data);
void	texture_mapping_y_draw(t_data *data, int x, int y);
int		mouse_rotate(int x, int y, void *param);

void	minimap_init(t_data *data);
void	minimap_draw(t_data *data);
#endif
