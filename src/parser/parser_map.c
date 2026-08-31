/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 20:32:19 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/31 18:25:19 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	directions_texture_init(t_data *data, char **tmps);
static int	floor_ceil_init(t_data *data, char **tmps);
static int	create_rgb(char *red, char *green, char *blue);
static void	termination(char *str);

int	direction_and_color_init(t_data *data, char *map_info)
{
	char	**tmps;

	if (is_valid(map_info, 0) != 0)
		return (0);
	tmps = ft_split(map_info, ' ');
	if (!tmps)
		return (1);
	if (is_valid(map_info, 1) == 0)
	{
		termination(tmps[1]);
		if (directions_texture_init(data, tmps) == 1)
			return (free_all(tmps), 1);
	}
	else if (is_valid(map_info, 2) == 0)
	{
		if (floor_ceil_init(data, tmps) != 0)
			return (free_all(tmps), 1);
	}
	return (free_all(tmps), 0);
}

static int	directions_texture_init(t_data *data, char **tmps)
{
	if (ft_strncmp(tmps[0], "NO", 2) == 0 && tmps[1])
	{
		data->map->texture_no = ft_strdup(tmps[1]);
		if (!data->map->texture_no)
			return (1);
	}
	else if (ft_strncmp(tmps[0], "SO", 2) == 0 && tmps[1])
	{
		data->map->texture_so = ft_strdup(tmps[1]);
		if (!data->map->texture_so)
			return (1);
	}
	else if (ft_strncmp(tmps[0], "WE", 2) == 0 && tmps[1])
	{
		data->map->texture_we = ft_strdup(tmps[1]);
		if (!data->map->texture_we)
			return (1);
	}
	else if (ft_strncmp(tmps[0], "EA", 2) == 0 && tmps[1])
	{
		data->map->texture_ea = ft_strdup(tmps[1]);
		if (!data->map->texture_ea)
			return (1);
	}
	return (0);
}

static int	floor_ceil_init(t_data *data, char **tmps)
{
	char	**rgb;

	rgb = ft_split(tmps[1], ',');
	if (!rgb)
		return (1);
	if (ft_strncmp(tmps[0], "F", 2) == 0 && tmps[1])
		data->map->color_f = create_rgb(rgb[0], rgb[1], rgb[2]);
	else if (ft_strncmp(tmps[0], "C", 2) == 0 && tmps[1])
		data->map->color_c = create_rgb(rgb[0], rgb[1], rgb[2]);
	free_all(rgb);
	return (0);
}

static int	create_rgb(char *red, char *green, char *blue)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(red);
	g = ft_atoi(green);
	b = ft_atoi(blue);
	return (r << 16 | g << 8 | b);
}

static void	termination(char *str)
{
	char	*t;

	t = ft_strchr(str, '\n');
	*t = '\0';
}
