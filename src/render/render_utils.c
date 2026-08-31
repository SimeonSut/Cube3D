/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 18:29:03 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/31 15:36:48 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	delta_dist_calculation(t_data *data)
{
	if (data->ray->ray_dir_x == 0)
		data->ray->delta_dist_x = 1e30;
	else
		data->ray->delta_dist_x = fabs(1 / data->ray->ray_dir_x);
	if (data->ray->ray_dir_y == 0)
		data->ray->delta_dist_y = 1e30;
	else
		data->ray->delta_dist_y = fabs(1 / data->ray->ray_dir_y);
}
