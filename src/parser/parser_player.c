#include "parser.h"

void	t_player_init(t_player *player, int x, int y, char *dir)
{
	if (*dir == 'N' || *dir == 'S' || *dir == 'W' || *dir == 'E')
	{
		player->player_nb += 1;
		//Le +0.5 évite que le joueur démarre collé à un 
		//mur ou pile sur une frontière de case (ce qui peut 
		//casser tes calculs de collision dès le premier frame).

		//D'où vient la valeur 0.66
		//La longueur (norme) du vecteur plane détermine l'ouverture du FOV, 
		//pas juste sa direction. Plus plane est long par rapport à dir
		//(qui est toujours de norme 1 ici), plus l'angle entre le rayon du
		//bord gauche et celui du bord droit est grand.
		player->pos_x = (double)x + 0.5;
		player->pos_y = (double)y + 0.5;
		if (*dir == 'N')
		{
			player->dir_x = 0;
			player->dir_y = -1;
			player->plane_x = 0.66;
			player->plane_y = 0;
		}
		else if (*dir == 'S')
		{
			player->dir_x = 0;
			player->dir_y = 1;
			player->plane_x = -0.66;
			player->plane_y = 0;
		}
		else if (*dir == 'W')
		{
			player->dir_x = -1;
			player->dir_y = 0;
			player->plane_x = 0;
			player->plane_y = -0.66;
		}
		else if (*dir == 'E')
		{
			player->dir_x = 1;
			player->dir_y = 0;
			player->plane_x = 0;
			player->plane_y = 0.66;
		}
        *dir = '0';
	}
}

int	player_position(t_data *data)
{
	int	i;
	int	j;

	if (!data->map.map)
		return (1);
	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{	
			t_player_init(&data->player, j, i, &data->map.map[i][j]);
			j++;			
		}
		i++;
	}
	return (0);
}
