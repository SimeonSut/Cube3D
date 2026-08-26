/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 15:01:29 by csamakka          #+#    #+#             */
/*   Updated: 2026/08/26 15:15:44 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_rotate(int x, void *param)
{
	t_data *data;
	double	old_dir_x;
	double 	old_plane_x;
	
	data = param;
	if (x < 1920 / 2)
	{
		old_dir_x = data->player->dir_x;
		data->player->dir_x = data->player->dir_x * cos(-0.03) - data->player->dir_y * sin(-0.03);
		data->player->dir_y = old_dir_x * sin(-0.03) + data->player->dir_y * cos(-0.03);
		old_plane_x = data->player->plane_x;
		data->player->plane_x = data->player->plane_x * cos(-0.03) - data->player->plane_y * sin(-0.03);
		data->player->plane_y = old_plane_x * sin(-0.03) + data->player->plane_y * cos(-0.03);
	}
	else
	{
		old_dir_x = data->player->dir_x;
		data->player->dir_x = data->player->dir_x * cos(0.03) - data->player->dir_y * sin(0.03);
		data->player->dir_y = old_dir_x * sin(0.03) + data->player->dir_y * cos(0.03);
		old_plane_x = data->player->plane_x;
		data->player->plane_x = data->player->plane_x * cos(0.03) - data->player->plane_y * sin(0.03);
		data->player->plane_y = old_plane_x * sin(0.03) + data->player->plane_y * cos(0.03);
	}
}