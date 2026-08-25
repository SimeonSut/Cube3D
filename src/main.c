/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:53:36 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/25 17:25:42 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "render.h"

//119 w
//115 s
//97 a
//100 d

void    movements(t_data *data, double x, double y)
{
	data->player->pos_x += x;
	data->player->pos_y += y;
}

int key_config(int keycode, void *param)
{
	t_data  *data;
	double  old_dir_x;
	double  old_plane_x;

	data = param;
	if (keycode == 'w')
		movements(data, 0, -0.05);
	else if (keycode == 's')
		movements(data, 0, 0.05);
	else if (keycode == 'a')
		movements(data, -0.05, 0);
	else if (keycode == 'd')
		movements(data, 0.05, 0);
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

int main(int ac, char **av)
{
	t_data  *data;

	if (ac != 2)
	{
		ft_putstr_fd("Expected a file .cub\n", 2);
		return (0);
	}
	data = t_data_init();
	if (!data)
		return (1);
	if (parsing(data, av) == 1)
		return (1);
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_putstr_fd("mlx init failed\n", 2);
		free_data(data);
		return (0);
	}
	data->mlx_win = mlx_new_window(data->mlx, 1920, 1080, "TMP_TEST");
	if (!data->mlx_win)
	{
		ft_putstr_fd("new window fail\n",2);
		free_data(data);
		return (0);
	}
	data->screen->img = mlx_new_image(data->mlx, 1920, 1080);
	data->screen->addr = mlx_get_data_addr(data->screen->img, &data->screen->bits_per_pixel,
		&data->screen->line_length, &data->screen->endian);
	map_d_render(data);
	mlx_hook(data->mlx_win, 2, 1L<<0, (int (*)())(void *)key_config, data);
	mlx_loop(data->mlx);
	return (0);
}
