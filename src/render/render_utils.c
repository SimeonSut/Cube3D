/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 18:29:03 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/01 17:00:47 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	delta_dist_calculation(t_data *data)
{
	if (data->ray->rdx == 0)
		data->ray->ddx = 1e30;
	else
		data->ray->ddx = fabs(1 / data->ray->rdx);
	if (data->ray->rdy == 0)
		data->ray->ddy = 1e30;
	else
		data->ray->ddy = fabs(1 / data->ray->rdy);
}

void	new_pos_cal(double *new_x, double *new_y, t_data *data, int key)
{
	if (key == 'w')
	{
		*new_x = data->p.pos_x + MOV_SPEED * data->p.dx;
		*new_y = data->p.pos_y + MOV_SPEED * data->p.dy;
	}
	else if (key == 's')
	{
		*new_x = data->p.pos_x - MOV_SPEED * data->p.dx;
		*new_y = data->p.pos_y - MOV_SPEED * data->p.dy;
	}
	else if (key == 'a')
	{
		*new_x = data->p.pos_x + MOV_SPEED * sidewalk(data, M_PI_2, 'a', 'x');
		*new_y = data->p.pos_y + MOV_SPEED * sidewalk(data, M_PI_2, 'a', 'y');
	}
	else if (key == 'd')
	{
		*new_x = data->p.pos_x - MOV_SPEED * sidewalk(data, M_PI_2, 'd', 'x');
		*new_y = data->p.pos_y - MOV_SPEED * sidewalk(data, M_PI_2, 'd', 'y');
	}
}
