/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 15:01:29 by csamakka          #+#    #+#             */
/*   Updated: 2026/08/31 18:36:01 by ssutarmi         ###   ########.fr       */
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
	rot_speed = 0.000015;
	data = param;
	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	data->player->dir_x = data->player->dir_x * cos(rot_speed * diff_x)
		- data->player->dir_y * sin(rot_speed * diff_x);
	data->player->dir_y = old_dir_x * sin(rot_speed * diff_x)
		+ data->player->dir_y * cos(rot_speed * diff_x);
	data->player->plane_x = data->player->plane_x * cos(rot_speed * diff_x)
		- data->player->plane_y * sin(rot_speed * diff_x);
	data->player->plane_y = old_plane_x * sin(rot_speed * diff_x)
		+ data->player->plane_y * cos(rot_speed * diff_x);
	mlx_mouse_move(data->mlx, data->mlx_win, W / 2, H / 2);
	(void)y;
	return (0);
}
