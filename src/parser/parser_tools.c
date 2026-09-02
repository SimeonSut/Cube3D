/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 20:32:24 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/02 18:48:57 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include "render.h"

int	string_count(char **strs);

int	flood_fill(char **map, int p_x, int p_y)
{
	if (p_x < 0 || p_y < 0 || p_y >= string_count(map))
		return (1);
	if (p_x >= (int)ft_strlen(map[p_y])
		|| map[p_y][p_x] == ' ' || map[p_y][p_x] == '\n')
		return (1);
	if (map[p_y][p_x] == '1' || map[p_y][p_x] == 'X')
		return (0);
	map[p_y][p_x] = 'X';
	if (flood_fill(map, p_x + 1, p_y) == 1)
		return (1);
	if (flood_fill(map, p_x - 1, p_y) == 1)
		return (1);
	if (flood_fill(map, p_x, p_y + 1) == 1)
		return (1);
	if (flood_fill(map, p_x, p_y - 1) == 1)
		return (1);
	return (0);
}

char	**dup_map(char **map)
{
	char	**dup;
	int		i;

	if (!map)
		return (NULL);
	dup = malloc(sizeof(char *) * (string_count(map) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (map[i])
	{
		dup[i] = ft_strdup(map[i]);
		if (!dup[i])
		{
			free_all(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

int	is_valid(char *line, int mode)
{
	if ((mode == 0 || mode == 1) && ft_strncmp(line, "NO ", 3) == 0)
		return (0);
	if ((mode == 0 || mode == 1) && ft_strncmp(line, "SO ", 3) == 0)
		return (0);
	if ((mode == 0 || mode == 1) && ft_strncmp(line, "WE ", 3) == 0)
		return (0);
	if ((mode == 0 || mode == 1) && ft_strncmp(line, "EA ", 3) == 0)
		return (0);
	if ((mode == 0 || mode == 2) && ft_strncmp(line, "F ", 2) == 0)
		return (0);
	if ((mode == 0 || mode == 2) && ft_strncmp(line, "C ", 2) == 0)
		return (0);
	return (1);
}

int	string_count(char **strs)
{
	int	i;

	if (!strs)
		return (0);
	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int	minilibx_init(t_data *data)
{
	data->screen.img = NULL;
	data->mlx_win = NULL;
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_putstr_fd(ERR_MLX, 2);
		return (free_data(data), 1);
	}
	if (texture_init(data, data->texture) == 1)
	{
		ft_putstr_fd(ERR_TXT, 2);
		return (free_data(data), 1);
	}
	data->mlx_win = mlx_new_window(data->mlx, W, H, "ICE CUBE");
	if (!data->mlx_win)
	{
		ft_putstr_fd(ERR_WIN, 2);
		return (free_data(data), 1);
	}
	data->screen.img = mlx_new_image(data->mlx, W, H);
	data->screen.addr = mlx_get_data_addr(data->screen.img,
			&data->screen.bits_per_pixel,
			&data->screen.line_length, &data->screen.endian);
	return (0);
}
