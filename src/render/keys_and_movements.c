/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_and_movements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 21:07:47 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/31 18:16:15 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include "render.h"

static void		movements(t_data *data, int keycode);
static double	sidewalk(t_data *data, double r, int keycode, int axis);
static int		collision(t_data *data, char key);

int key_config(int keycode, void *param)
{
	t_data  *data;
	double  old_dir_x;
	double  old_plane_x;

	data = param;
	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	if (keycode == 'w' || keycode == 's' || keycode == 'a' || keycode == 'd')
		movements(data, keycode);
	else if (keycode == 'q')
	{
		data->player->dir_x = data->player->dir_x * cos(-0.03) - data->player->dir_y * sin(-0.03);
		data->player->dir_y = old_dir_x * sin(-0.03) + data->player->dir_y * cos(-0.03);
		data->player->plane_x = data->player->plane_x * cos(-0.03) - data->player->plane_y * sin(-0.03);
		data->player->plane_y = old_plane_x * sin(-0.03) + data->player->plane_y * cos(-0.03);
	}
	else if (keycode == 'e')
	{
		data->player->dir_x = data->player->dir_x * cos(0.03) - data->player->dir_y * sin(0.03);
		data->player->dir_y = old_dir_x * sin(0.03) + data->player->dir_y * cos(0.03);
		data->player->plane_x = data->player->plane_x * cos(0.03) - data->player->plane_y * sin(0.03);
		data->player->plane_y = old_plane_x * sin(0.03) + data->player->plane_y * cos(0.03);
	}
	key_handler(keycode, data);
	return (0);
}

int	close_window(void *param)
{
	t_data *data;

	data = param;
	if (data->mlx)
	{
		mlx_loop_end(data->mlx);
		free_data(data);
		exit(1);
	}
	return (0);
}

static void	movements(t_data *data, int keycode)
{
	if (keycode == 'w')
	{
		if (collision(data, 'w'))
			return ;
		data->player->pos_x += MOV_SPEED * data->player->dir_x;
		data->player->pos_y += MOV_SPEED * data->player->dir_y;
	}
	else if (keycode == 's')
	{
		if (collision(data, 's'))
			return ;
		data->player->pos_x -= MOV_SPEED * data->player->dir_x;
		data->player->pos_y -= MOV_SPEED * data->player->dir_y;
	}
	else if (keycode == 'a')
	{
		if (collision(data, 'a'))
			return ;
		data->player->pos_x += MOV_SPEED * sidewalk(data, M_PI_2, 'a', 'x');
		data->player->pos_y += MOV_SPEED * sidewalk(data, M_PI_2, 'a', 'y');
	}
	else if (keycode == 'd')
	{
		if (collision(data, 'd'))
			return ;
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

static int	collision(t_data *data, char key)
{
	double	new_pos_x;
	double	new_pos_y;
	
	new_pos_x = 0.0;
	new_pos_y = 0.0;
	if (key == 'w')
	{
		new_pos_x = data->player->pos_x + MOV_SPEED * data->player->dir_x;
		new_pos_y = data->player->pos_y + MOV_SPEED * data->player->dir_y;
	}
	else if (key == 's')
	{
		new_pos_x = data->player->pos_x - MOV_SPEED * data->player->dir_x;
		new_pos_y = data->player->pos_y - MOV_SPEED * data->player->dir_y;
	}
	else if (key == 'a')
	{
		new_pos_x = data->player->pos_x + MOV_SPEED * sidewalk(data, M_PI_2, 'a', 'x');
		new_pos_y = data->player->pos_y + MOV_SPEED * sidewalk(data, M_PI_2, 'a', 'y');
	}
	else if (key == 'd')
	{
		new_pos_x = data->player->pos_x - MOV_SPEED * sidewalk(data, M_PI_2, 'd', 'x');
		new_pos_y = data->player->pos_y - MOV_SPEED * sidewalk(data, M_PI_2, 'd', 'y');
	}
	if (data->map->map[(int)new_pos_y][(int)new_pos_x] == '1'
			|| data->map->map[(int)new_pos_y][(int)new_pos_x] == '\n'
			|| data->map->map[(int)new_pos_y][(int)new_pos_x] == ' '
			|| data->map->map[(int)new_pos_y][(int)new_pos_x] == 0)
		return (1);
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