#ifndef PARSER_H
# define PARSER_H

# include "../get_next_line/get_next_line.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "cub3d.h"

char    **map_info_parser(char *map_path);
int	    dir_color_init(t_data *data, char *map_info);
int     map_data_init(t_data *data, char **map_info);
int     dir_init(t_data *data, char *map_info);
int	    floor_ceil_init(t_data *data, char *map_info);
char	**dup_map(char **map);
void	free_t_map(t_map map_data);
int     flood_fill(char **map_data, int p_x, int p_y);
int     player_data_init(t_data *data);
int	    player_position(t_data *data);

#endif