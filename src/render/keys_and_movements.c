/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_and_movements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 21:07:47 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/01 17:00:47 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include "render.h"

static void		movements(t_data *data, int key);
static int		key_handler(int key, t_data *data);

int	key_config(int keycode, void *param)
{
	t_data	*data;
	double	old_dir_x;
	double	old_plane_x;

	data = param;
	old_dir_x = data->p.dx;
	old_plane_x = data->p.plx;
	if (keycode == 'w' || keycode == 's' || keycode == 'a' || keycode == 'd')
		movements(data, keycode);
	else if (keycode == XK_LEFT)
	{
		data->p.dx = data->p.dx * cos(-0.03) - data->p.dy * sin(-0.03);
		data->p.dy = old_dir_x * sin(-0.03) + data->p.dy * cos(-0.03);
		data->p.plx = data->p.plx * cos(-0.03) - data->p.ply * sin(-0.03);
		data->p.ply = old_plane_x * sin(-0.03) + data->p.ply * cos(-0.03);
	}
	else if (keycode == XK_RIGHT)
	{
		data->p.dx = data->p.dx * cos(0.03) - data->p.dy * sin(0.03);
		data->p.dy = old_dir_x * sin(0.03) + data->p.dy * cos(0.03);
		data->p.plx = data->p.plx * cos(0.03) - data->p.ply * sin(0.03);
		data->p.ply = old_plane_x * sin(0.03) + data->p.ply * cos(0.03);
	}
	key_handler(keycode, data);
	return (0);
}

double	sidewalk(t_data *data, double r, int keycode, int axis)
{
	double	m;

	m = 0;
	if (keycode == 'a' && axis == 'x')
		m = (data->p.dx * cos(r * -1) + data->p.dy * sin(r));
	else if (keycode == 'a' && axis == 'y')
		m = (data->p.dx * sin(r * -1) + data->p.dy * cos(r));
	else if (keycode == 'd' && axis == 'x')
		m = (data->p.dx * cos(r * 3) - data->p.dy * sin(r * 3));
	else if (keycode == 'd' && axis == 'y')
		m = (data->p.dx * sin(r * 3) - data->p.dy * cos(r * 3));
	return (m);
}

static void	movements(t_data *data, int key)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = 0.0;
	new_pos_y = 0.0;
	new_pos_cal(&new_pos_x, &new_pos_y, data, key);
	if (data->map->map[(int)new_pos_y][(int)new_pos_x] == '1'
			|| data->map->map[(int)new_pos_y][(int)new_pos_x] == '\n'
			|| data->map->map[(int)new_pos_y][(int)new_pos_x] == ' '
			|| data->map->map[(int)new_pos_y][(int)new_pos_x] == 0)
		return ;
	data->p.pos_x = new_pos_x;
	data->p.pos_y = new_pos_y;
}

int	close_window(void *param)
{
	t_data	*data;

	data = param;
	if (data->mlx)
	{
		mlx_loop_end(data->mlx);
		free_data(data);
		exit(1);
	}
	return (0);
}

static int	key_handler(int key, t_data *data)
{
	if (key == ESC && data->mlx)
	{
		mlx_loop_end(data->mlx);
		free_data(data);
		exit(1);
	}
	return (0);
}
