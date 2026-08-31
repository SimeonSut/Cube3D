/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 15:01:29 by csamakka          #+#    #+#             */
/*   Updated: 2026/08/31 19:26:03 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include "render.h"

int	mouse_rotate(int x, int y, void *param)
{
	t_data	*data;
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;
	int		diff_x;

	diff_x = x - W / 2;
	rot_speed = ROTATION_SPEED;
	data = param;
	old_dir_x = data->p->dx;
	old_plane_x = data->p->plx;
	data->p->dx = data->p->dx * cos(rot_speed * diff_x)
		- data->p->dy * sin(rot_speed * diff_x);
	data->p->dy = old_dir_x * sin(rot_speed * diff_x)
		+ data->p->dy * cos(rot_speed * diff_x);
	data->p->plx = data->p->plx * cos(rot_speed * diff_x)
		- data->p->ply * sin(rot_speed * diff_x);
	data->p->ply = old_plane_x * sin(rot_speed * diff_x)
		+ data->p->ply * cos(rot_speed * diff_x);
	mlx_mouse_move(data->mlx, data->mlx_win, W / 2, H / 2);
	(void)y;
	return (0);
}
