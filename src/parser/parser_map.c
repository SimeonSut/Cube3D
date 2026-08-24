/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 20:32:19 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/18 20:35:44 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
