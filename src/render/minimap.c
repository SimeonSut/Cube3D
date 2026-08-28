/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 04:04:32 by csamakka          #+#    #+#             */
/*   Updated: 2026/08/29 00:52:03 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

static  int find_map_width(char **map);

void	minimap_draw(t_data *data)
{
	
}

static	void	draw_m(t_img *image, int size, int color)
{
	
}

void    minimap_init(t_data *data)
{
	int wrat;
	int hrat;
	
	wrat = 1920 / 5 / find_map_width(data->map->map);
	hrat = 1080 / 5 / string_count(data->map->map);
	data->mmap->mm->img = mlx_new_image(data->mlx, 1920 / 5, 1080 / 5);
	data->mmap->mp->img = mlx_new_image(data->mlx, wrat, hrat);
	data->mmap->mw->img = mlx_new_image(data->mlx, wrat, hrat);
	
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

static  int find_map_width(char **map)
{
	int	biggest;
	int	len;
	int	i;

	biggest = 0;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > biggest)
			biggest = len;
		i++;
	}
	return (biggest);
}

