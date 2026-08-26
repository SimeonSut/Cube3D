/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:53:36 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/26 15:18:38 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "render.h"

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
    texture_init(data);
	map_d_render(data);
	mlx_hook(data->mlx_win, 2, 1L<<0, (int (*)())(void *)key_config, data);
	mlx_hook(data->mlx_win, 6, 1L<<6,(int (*)())(void *)mouse_rotate, data);
	mlx_loop(data->mlx);
	return (0);
}
