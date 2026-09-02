/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:53:36 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/02 17:57:31 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include "render.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		ft_putstr_fd(ERR_ARG, 2);
		return (0);
	}
	t_data_init(&data);
	if (parsing(&data, av) == 1)
		return (1);
	if (minilibx_init(&data) == 1)
		return (1);
	minimap_init(&data);
	mlx_hook(data.mlx_win, 2, 1L << 0, (int (*)())(void *)key_config, &data);
	mlx_hook(data.mlx_win, 6, 1L << 6, (int (*)())(void *)mouse_rotate, &data);
	mlx_hook(data.mlx_win, 17, 0, (int (*)())(void *)close_window, &data);
	mlx_loop_hook(data.mlx, (int (*)())(void *)map_d_render, &data);
	mlx_mouse_move(data.mlx, data.mlx_win, W / 2, H / 2);
	mlx_mouse_hide(data.mlx, data.mlx_win);
	mlx_loop(data.mlx);
	return (0);
}
