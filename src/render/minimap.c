/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 04:04:32 by csamakka          #+#    #+#             */
/*   Updated: 2026/09/01 17:29:07 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include "render.h"

static int		find_map_width(char **map);
static void		draw_m(t_img *image, int width, int height, int color);

void	minimap_init(t_data *data)
{
	data->mmap.wrat = W / 5 / find_map_width(data->map.map);
	data->mmap.hrat = H / 5 / string_count(data->map.map);
	data->mmap.mm.img = mlx_new_image(data->mlx, (W / 5), (H / 5));
	data->mmap.mp.img = mlx_new_image(data->mlx, data->mmap.wrat,
			data->mmap.hrat);
	data->mmap.mw.img = mlx_new_image(data->mlx, data->mmap.wrat,
			data->mmap.hrat);
	data->mmap.mm.addr = mlx_get_data_addr(data->mmap.mm.img,
			&data->mmap.mm.bits_per_pixel, &data->mmap.mm.line_length,
			&data->mmap.mm.endian);
	data->mmap.mp.addr = mlx_get_data_addr(data->mmap.mp.img,
			&data->mmap.mp.bits_per_pixel, &data->mmap.mp.line_length,
			&data->mmap.mp.endian);
	data->mmap.mw.addr = mlx_get_data_addr(data->mmap.mw.img,
			&data->mmap.mw.bits_per_pixel, &data->mmap.mw.line_length,
			&data->mmap.mw.endian);
	draw_m(&data->mmap.mp, data->mmap.wrat, data->mmap.hrat, 0xFFFF0000);
	draw_m(&data->mmap.mw, data->mmap.wrat, data->mmap.hrat, 0x13031990);
}

void	minimap_draw(t_data *data)
{
	int	y;
	int	x;

	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->mmap.mm.img, 0, 0);
	y = 0;
	while (data->map.map[y])
	{
		x = 0;
		while (data->map.map[y][x])
		{
			if (data->map.map[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->mlx_win,
					data->mmap.mw.img, x * data->mmap.wrat,
					y * data->mmap.hrat);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->mmap.mp.img, (int)data->p.pos_x * data->mmap.wrat,
		(int)data->p.pos_y * data->mmap.hrat);
}

static	void	draw_m(t_img *image, int width, int height, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			my_mlx_pixel_put(image, x, y, color);
			x++;
		}
		y++;
	}
}

static int	find_map_width(char **map)
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
