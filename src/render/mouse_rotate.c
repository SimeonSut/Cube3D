/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 15:01:29 by csamakka          #+#    #+#             */
/*   Updated: 2026/08/26 16:27:21 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include "render.h"

int	mouse_rotate(int x, int y, void *param)
{
	t_data *data;
	double	old_dir_x;
	double 	old_plane_x;
	double	camera_x;
	
	data = param;
	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	camera_x = 2.0 * x / 1920 -1;
	if (x >= 0 && x < (1920 - 1) / 2)
	{
		data->player->dir_x = data->player->dir_x * cos(0.03 * camera_x) - data->player->dir_y * sin(0.03 * camera_x);
		data->player->dir_y = old_dir_x * sin(0.03 * camera_x) + data->player->dir_y * cos(0.03 * camera_x);
		data->player->plane_x = data->player->plane_x * cos(0.03 * camera_x) - data->player->plane_y * sin(0.03 * camera_x);
		data->player->plane_y = old_plane_x * sin(0.03 * camera_x) + data->player->plane_y * cos(0.03 * camera_x);
	}
	else if ( x >= 0 && x > (1920 - 1) / 2)
	{
		data->player->dir_x = data->player->dir_x * cos(0.03 * camera_x) - data->player->dir_y * sin(0.03 * camera_x);
		data->player->dir_y = old_dir_x * sin(0.03 * camera_x) + data->player->dir_y * cos(0.03 * camera_x);
		data->player->plane_x = data->player->plane_x * cos(0.03 * camera_x) - data->player->plane_y * sin(0.03 * camera_x);
		data->player->plane_y = old_plane_x * sin(0.03 * camera_x) + data->player->plane_y * cos(0.03 * camera_x);
	}
	(void)y;
	map_d_render(data);
	return (0);
}
