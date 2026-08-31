/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 20:32:22 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/31 18:27:16 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	t_player_init(t_player *player, int x, int y, char *dir);
static void	direction_init(t_player *player, char *dir);
static void	plane_init(t_player *player, char *dir);

int	player_data_init(t_data *data)
{
	int	i;
	int	j;

	if (!data->map->map)
		return (1);
	data->player->player_nb = 0;
	i = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			t_player_init(data->player, j, i, &data->map->map[i][j]);
			j++;
		}
		i++;
	}
	if (data->player->player_nb != 1)
	{
		printf("player number is %d\n", data->player->player_nb);
		return (1);
	}
	return (0);
}

static void	t_player_init(t_player *player, int x, int y, char *dir)
{
	if (*dir == 'N' || *dir == 'S' || *dir == 'W' || *dir == 'E')
	{
		player->player_nb += 1;
		player->pos_x = (double)x + 0.5;
		player->pos_y = (double)y + 0.5;
		direction_init(player, dir);
		plane_init(player, dir);
		*dir = '0';
	}
}

static void	direction_init(t_player *player, char *dir)
{
	if (*dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (*dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (*dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else if (*dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
}

static void	plane_init(t_player *player, char *dir)
{
	if (*dir == 'N')
	{
		player->plane_x = tan(FOV / 2.0);
		player->plane_y = 0;
	}
	else if (*dir == 'S')
	{
		player->plane_x = -1;
		player->plane_y = 0;
	}
	else if (*dir == 'W')
	{
		player->plane_x = 0;
		player->plane_y = -1;
	}
	else if (*dir == 'E')
	{
		player->plane_x = 0;
		player->plane_y = tan(FOV / 2.0);
	}
}
