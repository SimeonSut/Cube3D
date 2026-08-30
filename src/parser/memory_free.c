/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 12:37:03 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/30 12:55:14 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_t_map(t_map *map_data);
static void free_img_mem(t_data *new);

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->mlx && data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx && data->img && data->screen)
	{
		mlx_destroy_image(data->mlx, data->screen->img);
		free(data->screen->img);
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->player)
		free(data->player);
	if (data->map)
		free_t_map(data->map);
	free_img_mem(data);
	free(data);
}

static void free_img_mem(t_data *new)
{
	if (new->img)
		free(new->img);
	if (new->img_p)
		free(new->img_p);
	if (new->grill)
		free(new->grill);
	if (new->v_dir)
		free(new->v_dir);
	if (new->v_plane)
		free(new->v_plane);
	if (new->screen)
		free(new->screen);
	if (new->ray)
		free(new->ray);
	if (new->mmap)
		free(new->mmap->mm);
	if (new->mmap->mm)
		free(new->mmap->mm);
	if (new->mmap->mp)
		free(new->mmap->mp);
	if (new->mmap->mw)
		free(new->mmap->mw);
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
