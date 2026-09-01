/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 12:37:03 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/01 17:01:14 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_t_map(t_map *map_data);
static void	free_img_mem(t_data *data);

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->mlx && data->screen)
		mlx_destroy_image(data->mlx, data->screen->img);
	if (data->mlx && data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->map)
		free_t_map(data->map);
	free_img_mem(data);
	free(data);
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
	free(map_data);
}

static void	free_img_mem(t_data *data)
{
	if (data->screen)
		free(data->screen);
	if (data->ray)
		free(data->ray);
	if (data->mmap->mm)
		free(data->mmap->mm);
	if (data->mmap->mp)
		free(data->mmap->mp);
	if (data->mmap->mw)
		free(data->mmap->mw);
	if (data->mmap)
		free(data->mmap);
}
