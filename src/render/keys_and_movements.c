/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_and_movements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 21:07:47 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/25 22:12:50 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "render.h"

static void		movements(t_data *data, int keycode);
static double	sidewalk(t_data *data, double r, int keycode, int axis);

int key_config(int keycode, void *param)
{
	t_data  *data;
	double  old_dir_x;
	double  old_plane_x;

	data = param;
	if (keycode == 'w' || keycode == 's' || keycode == 'a' || keycode == 'd')
		movements(data, keycode);
	else if (keycode == 'q')
	{
		old_dir_x = data->player->dir_x;
		data->player->dir_x = data->player->dir_x * cos(-0.03) - data->player->dir_y * sin(-0.03);
		data->player->dir_y = old_dir_x * sin(-0.03) + data->player->dir_y * cos(-0.03);
		old_plane_x = data->player->plane_x;
		data->player->plane_x = data->player->plane_x * cos(-0.03) - data->player->plane_y * sin(-0.03);
		data->player->plane_y = old_plane_x * sin(-0.03) + data->player->plane_y * cos(-0.03);
	}
	else if (keycode == 'e')
	{
		old_dir_x = data->player->dir_x;
		data->player->dir_x = data->player->dir_x * cos(0.03) - data->player->dir_y * sin(0.03);
		data->player->dir_y = old_dir_x * sin(0.03) + data->player->dir_y * cos(0.03);
		old_plane_x = data->player->plane_x;
		data->player->plane_x = data->player->plane_x * cos(0.03) - data->player->plane_y * sin(0.03);
		data->player->plane_y = old_plane_x * sin(0.03) + data->player->plane_y * cos(0.03);
	}
	map_d_render(data);
	return (0);
}

static void	movements(t_data *data, int keycode)
{
	if (keycode == 'w')
	{
		data->player->pos_x += MOV_SPEED * data->player->dir_x;
		data->player->pos_y += MOV_SPEED * data->player->dir_y;
	}
	else if (keycode == 's')
	{
		data->player->pos_x -= MOV_SPEED * data->player->dir_x;
		data->player->pos_y -= MOV_SPEED * data->player->dir_y;
	}
	else if (keycode == 'a')
	{
		data->player->pos_x += MOV_SPEED * sidewalk(data, M_PI_2, 'a', 'x');
		data->player->pos_y += MOV_SPEED * sidewalk(data, M_PI_2, 'a', 'y');
	}
	else if (keycode == 'd')
	{
		data->player->pos_x += MOV_SPEED * sidewalk(data, M_2_PI, 'd', 'x');
		data->player->pos_y += MOV_SPEED * sidewalk(data, M_2_PI, 'd', 'y');
	}
}

static double	sidewalk(t_data *data, double r, int keycode, int axis)
{
	double	m;

	m = 0;
	if (keycode == 'a' && axis == 'x')
		m = (data->player->dir_x * cos(r * -1) + data->player->dir_y * sin(r));
	else if (keycode == 'a' && axis == 'y')
		m = (data->player->dir_x * sin(r * -1) + data->player->dir_y * cos(r));
	else if (keycode == 'd' && axis == 'x')
		m = (data->player->dir_x * cos(r * 3) - data->player->dir_y * sin(r * 3));
	else if (keycode == 'd' && axis == 'y')
		m = (data->player->dir_x * sin(r * 3) - data->player->dir_y * cos(r * 3));
	return (m);
}

/*static double   rotate_right_by(t_data *data, double r, int keycode, int axis)
{
	double	m;

	m = 0;
	if (keycode == 'q' && axis == 'x')
		m = data->player->dir_x * cos(r) - data->player->dir_y * sin(r);
	else if (keycode == 'q' && axis == 'y')
		m = (data->player->dir_x * sin(r * -1) + data->player->dir_y * cos(r));
	else if (keycode == 'e' && axis == 'x')
		m = (data->player->dir_x * cos(r * 3) - data->player->dir_y * sin(r * 3));
	else if (keycode == 'e' && axis == 'y')
		m = (data->player->dir_x * sin(r * 3) - data->player->dir_y * cos(r * 3));
	return (m);
}*/
