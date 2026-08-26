/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 21:13:54 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/26 15:16:56 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_map	*t_map_init(void);
static void	free_t_map(t_map *map_data);

t_data	*t_data_init(void)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->mlx = NULL;
	new->mlx_win = NULL;
	new->player = malloc(sizeof(t_player));
	if (!new->player)
	{
		free(new);
		return (NULL);
	}
	new->map = t_map_init();
	if (!new->map)
		return (free_data(new), NULL);
	new->img = malloc(sizeof(t_img));
	new->img_p = malloc(sizeof(t_img));
	new->grill = malloc(sizeof(t_img));
	new->v_dir = malloc(sizeof(t_img));
	new->v_plane = malloc(sizeof(t_img));
	new->screen = malloc(sizeof(t_img));
	new->ray = malloc(sizeof(t_ray));
	if (!new->screen)
		return (free_data(new), NULL);
	return (new);
}

static t_map	*t_map_init(void)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->map = NULL;
	new->texture_no = NULL;
	new->texture_so = NULL;
	new->texture_we = NULL;
	new->texture_ea = NULL;
	return (new);
}

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
}

int	minilibx_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_putstr_fd("mlx init failed\n", 2);
		free_data(data);
		return (1);
	}
	data->mlx_win = mlx_new_window(data->mlx, 1920, 1080, "TMP_TEST");
	if (!data->mlx_win)
	{
		ft_putstr_fd("new window fail\n",2);
		free_data(data);
		return (1);
	}
	data->screen->img = mlx_new_image(data->mlx, 1920, 1080);
	data->screen->addr = mlx_get_data_addr(data->screen->img, &data->screen->bits_per_pixel,
		&data->screen->line_length, &data->screen->endian);
	return (0);
}


/*
int    exit_game(t_data *data)
{
    free_all_img(data);
    mlx_destroy_window(data->mlx, data->window);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    free_all(data->map);
    exit(0);
}*/