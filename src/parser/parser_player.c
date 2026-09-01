/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 20:32:22 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/01 17:01:00 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	t_player_init(t_player *player, int x, int y, char *dir);
static void	direction_init(t_player *player, char *dir);
static void	plane_init(t_player *player, char *dir);

int	player_data_init(t_data *data)
{
	int	i;
	int	j;

	if (!data->map->map)
		return (1);
	data->p.player_nb = 0;
	i = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (t_player_init(&data->p, j, i, &data->map->map[i][j]) == 1)
				return (1);
			j++;
		}
		i++;
	}
	if (data->p.player_nb != 1)
	{
		printf("player number is %d\n", data->p.player_nb);
		return (1);
	}
	return (0);
}

static int	t_player_init(t_player *player, int x, int y, char *dir)
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
	else if (*dir != '1' && *dir != '0' && *dir != ' ' && *dir != '\n')
		return (1);
	return (0);
}

static void	direction_init(t_player *player, char *dir)
{
	if (*dir == 'N')
	{
		player->dx = 0;
		player->dy = -1;
	}
	else if (*dir == 'S')
	{
		player->dx = 0;
		player->dy = 1;
	}
	else if (*dir == 'W')
	{
		player->dx = -1;
		player->dy = 0;
	}
	else if (*dir == 'E')
	{
		player->dx = 1;
		player->dy = 0;
	}
}

static void	plane_init(t_player *player, char *dir)
{
	if (*dir == 'N')
	{
		player->plx = tan(FOV / 2.0);
		player->ply = 0;
	}
	else if (*dir == 'S')
	{
		player->plx = -1;
		player->ply = 0;
	}
	else if (*dir == 'W')
	{
		player->plx = 0;
		player->ply = -1;
	}
	else if (*dir == 'E')
	{
		player->plx = 0;
		player->ply = tan(FOV / 2.0);
	}
}
