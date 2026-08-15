#include "parser.h"

int	dir_color_init(t_data *data, char *map_info)
{
	if (ft_strnstr(map_info, "NO ", 3) != NULL
		|| ft_strnstr(map_info, "SO ", 3) != NULL
		|| ft_strnstr(map_info, "WE ", 3) != NULL
		|| ft_strnstr(map_info, "EA ", 3) != NULL)
	{
		if (dir_init(data, map_info) != 0)
			return (1);
	}
	else if (ft_strnstr(map_info, "F ", 2) != NULL
		|| ft_strnstr(map_info, "C ", 2) != NULL)
	{
		if (floor_ceil_init(data, map_info) != 0)
			return (1);
	}
	return (0);
}

void	free_t_map(t_map map_data)
{
	if (map_data.texture_no)
		free(map_data.texture_no);
	if (map_data.texture_so)
		free(map_data.texture_so);
	if (map_data.texture_we)
		free(map_data.texture_we);
	if (map_data.texture_ea)
		free(map_data.texture_ea);
	if (map_data.map)
		free_all(map_data.map);
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
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

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
