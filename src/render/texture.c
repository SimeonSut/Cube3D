/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 14:30:26 by csamakka          #+#    #+#             */
/*   Updated: 2026/08/31 18:49:36 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static int	texture_select(t_ray *ray);

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
	data->texture[data->tex_index].texture_x
		= (int)(data->ray->wall_x * data->texture[data->tex_index].width);
	data->texture[data->tex_index].step
		= (double)data->texture[data->tex_index].height
		/ data->ray->line_height;
	data->texture[data->tex_index].texture_pos = (data->ray->draw_start - H
			/ 2 + data->ray->line_height / 2)
		* data->texture[data->tex_index].step;
}

static int	texture_select(t_ray *ray)
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
	int	tex_i;

	tex_i = data->tex_index;
	data->texture[tex_i].texture_y
		= (int)data->texture[tex_i].texture_pos
		& (data->texture[tex_i].height - 1);
	data->texture[tex_i].pixel_color
		= *(unsigned int *)(data->texture[tex_i].addr
			+ (data->texture[tex_i].texture_y
				* data->texture[tex_i].line_length
				+ data->texture[tex_i].texture_x
				* (data->texture[tex_i].bits_per_pixel / 8)));
	my_mlx_pixel_put(data->screen, x, y, data->texture[tex_i].pixel_color);
	data->texture[tex_i].texture_pos
		+= data->texture[tex_i].step;
}

void	texture_init(t_data	*data)
{
	t_texture	*txt;

	txt = data->texture;
	txt[0].img = mlx_xpm_file_to_image(data->mlx, data->map->texture_no,
			&data->texture[0].width, &data->texture[0].height);
	txt[1].img = mlx_xpm_file_to_image(data->mlx, data->map->texture_so,
			&data->texture[1].width, &data->texture[1].height);
	txt[2].img = mlx_xpm_file_to_image(data->mlx, data->map->texture_we,
			&data->texture[2].width, &data->texture[2].height);
	txt[3].img = mlx_xpm_file_to_image(data->mlx, data->map->texture_ea,
			&data->texture[3].width, &data->texture[3].height);
	txt[0].addr = mlx_get_data_addr(data->texture[0].img,
			&data->texture[0].bits_per_pixel, &data->texture[0].line_length,
			&data->texture[0].endian);
	txt[1].addr = mlx_get_data_addr(data->texture[1].img,
			&data->texture[1].bits_per_pixel, &data->texture[1].line_length,
			&data->texture[1].endian);
	txt[2].addr = mlx_get_data_addr(data->texture[2].img,
			&data->texture[2].bits_per_pixel, &data->texture[2].line_length,
			&data->texture[2].endian);
	txt[3].addr = mlx_get_data_addr(data->texture[3].img,
			&data->texture[3].bits_per_pixel, &data->texture[3].line_length,
			&data->texture[3].endian);
}
