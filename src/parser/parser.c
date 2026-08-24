/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 20:32:17 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/18 20:56:42 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**map_info_parser(char *map_path);
static int	map_data_init(t_data *data, char **map_info);
static char	**parser_construct(int fd);

/**
NECESSARY ADDITION 

Add function to filter inputs of the map

Conditions :

Only 0 and 1 except for one char letter.
The ONLY char letter is either N, S, E, or W

*/

int			map_parser(t_data *data, char **av)
{
	char	**map_info;

	map_info = map_info_parser(av[1]);
	if (!map_info)
		return (1);
	if (map_data_init(data, map_info) != 0)
	{
		ft_putstr_fd("Map parsing failed !\n", 2);
		free_all(map_info);
		free_t_map(data->map);
		return (1);
	}
	free_all(map_info);
	if (player_data_init(&data) == 1)
	{
		ft_putstr_fd("Player init error\n", 2);
		free_t_map(data.map);
		return (1);
	}
	return (0);
}

static char	**map_info_parser(char *map_path)
{
	int		path_len;
	int		fd;
	char	**map;

	path_len = 0;
	while (map_path[path_len] && map_path[path_len] != '.')// TEST NEEDED : test if needs to stop at path_len or path_len + 1
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

static int	map_data_init(t_data *data, char **map_info)
{
	int	i;
	int	map_counter;

	data->map.map = NULL;
	map_counter = 0;
	i = -1;
	while (map_info[++i])
	{
		if (dir_color_init(data, map_info[i]) != 0)
			return (1);
		if (map_info[i][0] != '\n' && ft_strncmp(map_info[i], "NO", 2) != 0
				&& ft_strncmp(map_info[i], "SO", 2) != 0
				&& ft_strncmp(map_info[i], "WE", 2) != 0
				&& ft_strncmp(map_info[i], "EA", 2) != 0 
				&& ft_strncmp(map_info[i], "F ", 2) != 0
				&& ft_strncmp(map_info[i], "C ", 2) != 0)
		{
			data->map.map = realloc(data->map.map, sizeof(char *) * (2 + map_counter));
			if (!data->map.map)
				return (1);
			data->map.map[map_counter] = ft_strdup(map_info[i]);
			data->map.map[map_counter++ + 1] = NULL;
		}
	}
	return (0);
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
