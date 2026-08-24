/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 21:13:54 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/24 21:15:20 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_data	*t_data_init(void)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->mlx = NULL;
	new->mlx_win = NULL;
	new->player = malloc(sizeof(t_player));
	if (!new->player)
	{
		free(new);
		return (NULL);
	}
	new->map = NULL;
	new->img = NULL;
	new->img_p = NULL;
	new->screen = NULL;
	return (new);
}

t_map	*t_map_init(void)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->map = NULL;
	new->texture_no = NULL;
	new->texture_so = NULL;
	new->texture_we = NULL;
	new->texture_ea = NULL;
	return (new);
}

void	free_t_map(t_map *map_data)
{
	if (map_data->texture_no)
		free(map_data->texture_no);
	if (map_data->texture_so)
		free(map_data->texture_so);
	if (map_data->texture_we)
		free(map_data->texture_we);
	if (map_data->texture_ea)
		free(map_data->texture_ea);
	if (map_data->map)
		free_all(map_data->map);
}
