#include "parser.h"

char   **parser_construct(int fd)
{
	int     i;
	char    *map_read;
	char    **map;

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

char    **map_info_parser(char *map_path)
{
	int     path_len;
	int     fd;
	char    **map;

	path_len = ft_strlen(map_path);
	if (ft_strncmp(map_path + path_len - 4, ".cub", 5) != 0)
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

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	dir_init(t_data *data, char *map_info)
{
	char **tmps;

	tmps = ft_split(map_info, ' ');
	if (!tmps)
		return (1);
	if (ft_strncmp(tmps[0], "NO", 3) == 0 && tmps[1])
		data->map.texture_no = ft_strdup(tmps[1]);
	else if (ft_strncmp(tmps[0], "SO", 3) == 0 && tmps[1])
		data->map.texture_so = ft_strdup(tmps[1]);
	else if (ft_strncmp(tmps[0], "WE", 3) == 0 && tmps[1])
		data->map.texture_we = ft_strdup(tmps[1]);
	else if (ft_strncmp(tmps[0], "EA", 3) == 0 && tmps[1])
		data->map.texture_ea = ft_strdup(tmps[1]);
	free_all(tmps);
	return (0);
}

int	floor_ceil_init(t_data *data, char *map_info)
{
	char **tmps;
	char **rgb;

	tmps = ft_split(map_info, ' ');
	if (!tmps)
		return (1);
	rgb = ft_split(tmps[1], ',');
	if (!rgb || !(rgb[0] && rgb[1] && rgb[2]))
		return (free_all(tmps), 1);
	if (ft_strncmp(tmps[0], "F", 2) == 0 && tmps[1])
		data->map.color_f = create_rgb(ft_atoi(rgb[0]),
			ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	else if (ft_strncmp(tmps[0], "C", 2) == 0 && tmps[1])
		data->map.color_c = create_rgb(ft_atoi(rgb[0]),
			ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	free_all(tmps);
	free_all(rgb);
	rgb = NULL;
	return (0);
}
