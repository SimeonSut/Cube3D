/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 21:13:06 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/31 17:15:00 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	side_dist_calculation(t_data *data);
static void	hit_determination(t_data *data);
static void	column_drawing(t_data *data, int x);
static void	draw_start_and_end(t_data *data);

void    map_d_render(t_data *data)
{
	int x;
	ft_memset(data->screen->addr, 0, data->screen->line_length * H);
	x = 0;
	while (x < W)
	{
		data->ray->camera_x = 2.0 * x / W - 1;
		data->ray->ray_dir_x = data->player->dir_x + data->player->plane_x * data->ray->camera_x;
		data->ray->ray_dir_y = data->player->dir_y + data->player->plane_y * data->ray->camera_x;
		data->ray->map_x = (int)data->player->pos_x;
		data->ray->map_y = (int)data->player->pos_y;
		delta_dist_calculation(data);
		side_dist_calculation(data);
		hit_determination(data);
		if (data->ray->side == 0)
			data->ray->perp_wall_dist = data->ray->side_dist_x - data->ray->delta_dist_x;
		else
			data->ray->perp_wall_dist = data->ray->side_dist_y - data->ray->delta_dist_y;
		data->ray->line_height = H / data->ray->perp_wall_dist;
		draw_start_and_end(data);
		texture_mapping_x(data);
		column_drawing(data, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->screen->img, 0, 0);
	minimap_draw(data);
}

static void	side_dist_calculation(t_data *data)
{
	if (data->ray->ray_dir_x < 0)
	{
		data->ray->step_x = -1;
		data->ray->side_dist_x = (data->player->pos_x - (double)data->ray->map_x) * data->ray->delta_dist_x;
	}
	else
	{
		data->ray->step_x = 1;
		data->ray->side_dist_x = ((double)data->ray->map_x + 1.0 - data->player->pos_x) * data->ray->delta_dist_x;
	}
	if (data->ray->ray_dir_y < 0)
	{
		data->ray->step_y = -1;
		data->ray->side_dist_y = (data->player->pos_y - (double)data->ray->map_y) * data->ray->delta_dist_y;
	}
	else
	{
		data->ray->step_y = 1;
		data->ray->side_dist_y = ((double)data->ray->map_y + 1.0 - data->player->pos_y) * data->ray->delta_dist_y;
	}
}

static void	hit_determination(t_data *data)
{
	data->ray->hit = 0;
	while (!data->ray->hit)
	{
		if (data->ray->side_dist_x < data->ray->side_dist_y)
		{
			data->ray->side_dist_x += data->ray->delta_dist_x;
			data->ray->map_x += data->ray->step_x;
			data->ray->side = 0;
		}
		else
		{
			data->ray->side_dist_y += data->ray->delta_dist_y;
			data->ray->map_y += data->ray->step_y;
			data->ray->side = 1;
		}
		if (data->map->map[data->ray->map_y][data->ray->map_x] == '1')
			data->ray->hit = 1;
	}
}

static void	column_drawing(t_data *data, int x)
{
	int	y;

	y = 0;
	while (y < H)
	{
		if (y >= data->ray->draw_start && y <= data->ray->draw_end)
		{
			texture_mapping_y_draw(data, x, y);
		}
		else if (y < (H / 2))
			my_mlx_pixel_put(data->screen, x, y, data->map->color_f);
		else
			my_mlx_pixel_put(data->screen, x, y, data->map->color_c);
		y++;
	}
}

static void	draw_start_and_end(t_data *data)
{
	data->ray->draw_start = -data->ray->line_height / 2 + H / 2;
	data->ray->draw_end = data->ray->line_height / 2 + H / 2;
	if (data->ray->draw_start < 0)
		data->ray->draw_start = 0;
	if (data->ray->draw_end >= H)
		data->ray->draw_end = H - 1;
}
