/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 21:13:11 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/31 18:16:45 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../get_next_line/get_next_line.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "cub3d.h"

//PARSER.C
int		parsing(t_data *data, char **av);

//PARSER_MAP.C
int		direction_and_color_init(t_data *data, char *map_info);

//PARSER_PLAYER.C
int		player_data_init(t_data *data);

//PARSER_TOOLS.C
char	**dup_map(char **map);
int		flood_fill(char **map_data, int p_x, int p_y);
int		is_valid(char *line, int mode);
int		string_count(char **strs);

//MEMORY.C
t_data	*t_data_init(void);
void	free_data(t_data *data);
int		minilibx_init(t_data *data);

#endif