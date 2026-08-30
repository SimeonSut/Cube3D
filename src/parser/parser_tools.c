/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 20:32:24 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/30 20:38:19 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	string_count(char **strs);

int flood_fill(char **map, int p_x, int p_y)
{
	int		height;
	int		widgth;

	height = string_count(map);
	if (p_y < 0 || p_x < 0)
		return (0);
	widgth = ft_strlen(map[p_y]) - 1;
	if (p_x >= widgth || p_y >= height || map[p_y][p_x] == '1'
		|| map[p_y][p_x] == 'X')
		return (0);
	if (!map[p_y + 1] || map[p_y][p_x + 1] == '\n' || p_y - 1 < 0
		|| p_x - 1 < 0 || map[p_y + 1][p_x] == ' '
		|| map[p_y][p_x + 1] == ' ' || map[p_y - 1][p_x] == ' '
		|| map[p_y][p_x - 1] == ' ')
		return (1);
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
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_putstr_fd("mlx init failed\n", 2);
		free_data(data);
		return (1);
	}
	data->mlx_win = mlx_new_window(data->mlx, W, H, "TMP_TEST");
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
