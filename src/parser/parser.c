/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 20:32:17 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/01 17:09:45 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**map_info_parser(char *map_path);
static char	**parser_construct(int fd);
static int	map_data_init(t_data *data, char **map_info);
static int	check_validity(t_data *data);

int	parsing(t_data *data, char **av)
{
	char	**map_info;

	map_info = map_info_parser(av[1]);
	if (!map_info)
		return (1);
	if (map_data_init(data, map_info) != 0)
	{
		ft_putstr_fd("Map parsing failed !\n", 2);
		return (free_data(data), free_all(map_info), 1);
	}
	if (player_data_init(data) == 1)
	{
		ft_putstr_fd("Player init error\n", 2);
		return (free_data(data), 1);
	}
	if (flood_fill(data->map.map, data->p.pos_x, data->p.pos_y) == 1)
	{
		ft_putstr_fd("Map invalid: Player is not surround by wall !\n", 2);
		return (free_data(data), free_all(map_info), 1);
	}
	free_all(map_info);
	if (check_validity(data) == 1)
		return (free_data(data), 1);
	return (0);
}

static char	**map_info_parser(char *map_path)
{
	int		path_len;
	int		fd;
	char	**map;

	path_len = 0;
	while (map_path[path_len] && map_path[path_len] != '.')
		path_len++;
	if (ft_strncmp(map_path + path_len, ".cub", 5) != 0)
	{
		ft_putstr_fd("Path invalid\n", 2);
		return (NULL);
	}
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = parser_construct(fd);
	if (!map)
		return (NULL);
	return (map);
}

static char	**parser_construct(int fd)
{
	int		i;
	char	*map_read;
	char	**map;

	map = NULL;
	i = 0;
	while (1)
	{
		map_read = get_next_line(fd);
		if (!map_read)
			break ;
		map = realloc(map, sizeof(char *) * (2 + i));
		if (!map)
			return (NULL);
		map[i] = ft_strdup(map_read);
		map[i + 1] = NULL;
		free(map_read);
		i++;
	}
	return (map);
}

static int	map_data_init(t_data *data, char **map_info)
{
	int	i;
	int	map_counter;

	data->map.map = NULL;
	map_counter = 0;
	i = -1;
	while (map_info[++i])
	{
		if (direction_and_color_init(data, map_info[i]) != 0)
			return (1);
		if (map_info[i][0] != '\n' && is_valid(map_info[i], 0) != 0)
		{
			data->map.map = realloc(data->map.map, sizeof(char *)
					* (2 + map_counter));
			if (!data->map.map)
				return (1);
			data->map.map[map_counter] = ft_strdup(map_info[i]);
			data->map.map[map_counter++ + 1] = NULL;
		}
	}
	return (0);
}

static int	check_validity(t_data *data)
{
	int	result;

	result = 0;
	if (!data->map.map)
		result = 1;
	if (!data->map.texture_no)
		result = 1;
	if (!data->map.texture_so)
		result = 1;
	if (!data->map.texture_ea)
		result = 1;
	if (!data->map.texture_we)
		result = 1;
	if (!data->map.color_f)
		result = 1;
	if (!data->map.color_c)
		result = 1;
	if (result == 1)
		ft_putstr_fd("wrong map specifications entry\n", STDERR_FILENO);
	return (result);
}

/*
NO sprites/colorstone.xpm
SO sprites/bluestone.xpm
WE sprites/wood.xpm
EA sprites/greystone.xpm

F 160,160,160
C 51,153,255

 11111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001111
11111111101100000111000000001
10000000001100000111110111111
1111010111111101100000010001
11110011111111011101010010001
11000000110101011100000010001
10000000000000001100000000001
10000000000000001101010010001
11000001110101011111011110E01
11110111 1110101 111011000001
 111111   11111   1111111111
*/
