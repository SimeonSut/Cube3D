/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 04:04:32 by csamakka          #+#    #+#             */
/*   Updated: 2026/08/27 04:28:41 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    minimap_init(t_data *data)
{
    int wrat;
    int hrat;
    
    wrat = 1920 / (1920 / 2);
    hrat = 1080 / (1080 / 2);
    data->mmap->mm->img = mlx_new_image(data->mlx, 1920 / 5, 1080 / 5);
    data->mmap->mp->img = mlx_new_image(data->mlx, wrat, hrat);
    data->mmap->mw->img = mlx_new_image(data->mlx, wrat * 5, hrat * 5);
    
    data->mmap->mm->addr = mlx_get_data_addr(data->mlx,
        data->mmap->mm->bits_per_pixel, data->mmap->mm->line_length,
        data->mmap->mm->endian);
    data->mmap->mp->addr = mlx_get_data_addr(data->mlx,
        data->mmap->mp->bits_per_pixel, data->mmap->mp->line_length,
        data->mmap->mp->endian);
    data->mmap->mw->addr = mlx_get_data_addr(data->mlx,
        data->mmap->mw->bits_per_pixel, data->mmap->mw->line_length,
        data->mmap->mw->endian);
}