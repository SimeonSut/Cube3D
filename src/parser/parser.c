#include "parser.h"

int    map_data_init(t_data *data, char **map_info)
{
	int     i;
	int     map_counter;

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

int	player_data_init(t_data *data)
{
	data->player.player_nb = 0;
	if (player_position(data) == 1)
		return (1);
	if (data->player.player_nb < 1 || data->player.player_nb > 1)
		return (1);
	return (0);
}
