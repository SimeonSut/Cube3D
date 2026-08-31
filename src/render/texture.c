/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 14:30:26 by csamakka          #+#    #+#             */
/*   Updated: 2026/08/31 15:25:44 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static	int	texture_select(t_ray *ray);

void	texture_mapping_x(t_data *data)
{
	data->tex_index = texture_select(data->ray);
	if (data->ray->side == 0)
		data->ray->wall_x = data->player->pos_y + data->ray->perp_wall_dist
			* data->ray->ray_dir_y;
	else
		data->ray->wall_x = data->player->pos_x + data->ray->perp_wall_dist
			* data->ray->ray_dir_x;
	data->ray->wall_x -= floor(data->ray->wall_x);
	data->texture[data->tex_index].texture_x =
		(int)(data->ray->wall_x * data->texture[data->tex_index].width);
	data->texture[data->tex_index].step =
		(double)data->texture[data->tex_index].height / data->ray->line_height;
	data->texture[data->tex_index].texture_pos = (data->ray->draw_start - H /
		2 + data->ray->line_height / 2) * data->texture[data->tex_index].step;
}

static	int	texture_select(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (ray->ray_dir_y < 0)
			return (0);
		else
			return (1);
	}
}

void	texture_mapping_y_draw(t_data *data, int x, int y)
{
	data->texture[data->tex_index].texture_y =
		(int)data->texture[data->tex_index].texture_pos
		& (data->texture[data->tex_index].height - 1);
	data->texture[data->tex_index].pixel_color =
		*(unsigned int *)(data->texture[data->tex_index].addr
			+ (data->texture[data->tex_index].texture_y
			* data->texture[data->tex_index].line_length
			+ data->texture[data->tex_index].texture_x
			* (data->texture[data->tex_index].bits_per_pixel / 8)));
	my_mlx_pixel_put(data->screen, x, y, data->texture[data->tex_index].pixel_color);
	data->texture[data->tex_index].texture_pos
		+= data->texture[data->tex_index].step;
}

// charger les fichiers xpm
void	texture_init(t_data	*data)
{
	data->texture[0].img = mlx_xpm_file_to_image(data->mlx, data->map->texture_no,
		&data->texture[0].width, &data->texture[0].height);
	data->texture[1].img = mlx_xpm_file_to_image(data->mlx, data->map->texture_so,
		&data->texture[1].width, &data->texture[1].height);
	data->texture[2].img = mlx_xpm_file_to_image(data->mlx, data->map->texture_we,
		&data->texture[2].width, &data->texture[2].height);
	data->texture[3].img = mlx_xpm_file_to_image(data->mlx, data->map->texture_ea,
		&data->texture[3].width, &data->texture[3].height);
	data->texture[0].addr = mlx_get_data_addr(data->texture[0].img,
		&data->texture[0].bits_per_pixel, &data->texture[0].line_length,
		&data->texture[0].endian);
	data->texture[1].addr = mlx_get_data_addr(data->texture[1].img,
		&data->texture[1].bits_per_pixel, &data->texture[1].line_length,
		&data->texture[1].endian);
	data->texture[2].addr = mlx_get_data_addr(data->texture[2].img,
		&data->texture[2].bits_per_pixel, &data->texture[2].line_length,
		&data->texture[2].endian);
	data->texture[3].addr = mlx_get_data_addr(data->texture[3].img,
		&data->texture[3].bits_per_pixel, &data->texture[3].line_length,
		&data->texture[3].endian);
}
