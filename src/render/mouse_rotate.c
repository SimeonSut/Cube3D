/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 15:01:29 by csamakka          #+#    #+#             */
/*   Updated: 2026/08/26 18:20:54 by csamakka         ###   ########.fr       */
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
	double	rot_speed;
	int		delta_x;
	
	delta_x = (x - (1920 / 2)) / 3;
	rot_speed = 0.001;
	data = param;
	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	
	data->player->dir_x = data->player->dir_x * cos(rot_speed * delta_x) - data->player->dir_y * sin(rot_speed * delta_x);
	data->player->dir_y = old_dir_x * sin(rot_speed * delta_x) + data->player->dir_y * cos(rot_speed * delta_x);
	
	data->player->plane_x = data->player->plane_x * cos(rot_speed * delta_x) - data->player->plane_y * sin(rot_speed * delta_x);
	data->player->plane_y = old_plane_x * sin(rot_speed * delta_x) + data->player->plane_y * cos(rot_speed * delta_x);
	map_d_render(data);
	
	(void)y;
	return (0);
}
