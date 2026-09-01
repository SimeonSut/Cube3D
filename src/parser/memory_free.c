/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 12:37:03 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/01 18:42:20 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_t_map(t_map *map_data);
static void	free_images(t_data *data);

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->mlx && data->screen.img)
		mlx_destroy_image(data->mlx, data->screen.img);
	if (data->mlx && data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	free_images(data);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free_t_map(&data->map);
}

static void	free_t_map(t_map *map_data)
{
	if (map_data->texture_no)
		free(map_data->texture_no);
	if (map_data->texture_so)
		free(map_data->texture_so);
	if (map_data->texture_we)
		free(map_data->texture_we);
	if (map_data->texture_ea)
		free(map_data->texture_ea);
	if (map_data->map)
		free_all(map_data->map);
}

static void	free_images(t_data *data)
{
	if (data->texture[0].img)
		mlx_destroy_image(data->mlx, data->texture[0].img);
	if (data->texture[1].img)
		mlx_destroy_image(data->mlx, data->texture[1].img);
	if (data->texture[2].img)
		mlx_destroy_image(data->mlx, data->texture[2].img);
	if (data->texture[3].img)
		mlx_destroy_image(data->mlx, data->texture[3].img);
	if (data->mmap.mm.img)
		mlx_destroy_image(data->mlx, data->mmap.mm.img);
	if (data->mmap.mp.img)
		mlx_destroy_image(data->mlx, data->mmap.mp.img);
	if (data->mmap.mw.img)
		mlx_destroy_image(data->mlx, data->mmap.mw.img);
}
