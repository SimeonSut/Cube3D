/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 21:13:06 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/25 21:14:41 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void    my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    draw_squar(void *img, int size, int color, int mode)
{
	int y;
	int x;

	if (mode == 0)
	{
		y = 0;
		while (y < size)
		{
			x = 0;
			while (x < size)
			{
				if (y == 0 || y == size - 1)
					my_mlx_pixel_put(img, x, y, color);
				else if (x == 0 || x == size - 1)
					my_mlx_pixel_put(img, x, y, color);
				x++;
			}
			y++;
		}
	}
	else
	{
		y = 0;
		while (y < size)
		{
			x = 0;
			while (x < size)
			{
				my_mlx_pixel_put(img, x, y, color);
				x++;
			}
			y++;
		}
	}
}

void    map_render(t_data *data)
{
	int y;
	int x;

	mlx_clear_window(data->mlx, data->mlx_win);
	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img,
					x * 64, y * 64);
			else
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->grill->img,
					x * 64, y * 64);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_p->img,
		data->player->pos_x * 64, data->player->pos_y * 64);
	int len = 0;
	int tile_size = 64;

	while (len < tile_size)
	{
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->v_dir->img,
			(data->player->pos_x * tile_size) + data->player->dir_x * len,
			(data->player->pos_y * tile_size) + data->player->dir_y * len);
		len++;
	}
	x = 0;
	double nb_rays = tan(FOV / 2) * tile_size;
	while (x < nb_rays)
	{
		double camera_x = 2.0 * x / nb_rays - 1;
		double ray_dir_x = data->player->dir_x + data->player->plane_x * camera_x;
		double ray_dir_y = data->player->dir_y + data->player->plane_y * camera_x;
		int map_x = (int)data->player->pos_x;
		int map_y = (int)data->player->pos_y;
		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);
		double side_dist_x = 0;
		double side_dist_y = 0;
		int step_x;
		int step_y;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->player->pos_x - (double)map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = ((double)map_x + 1.0 - data->player->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->player->pos_y - (double)map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = ((double)map_y + 1.0 - data->player->pos_y) * delta_dist_y;
		}
		int hit = 0;
		len = 0;
		while (!hit)
		{
			
			if (side_dist_x < side_dist_y)
			{
				while (len < (side_dist_x * tile_size))
				{
					mlx_put_image_to_window(data->mlx, data->mlx_win, data->v_dir->img,
						(data->player->pos_x * tile_size) + ray_dir_x * len,
						(data->player->pos_y * tile_size) + ray_dir_y * len);
					len++;
				}
				side_dist_x += delta_dist_x;
				map_x += step_x;
			}
			else
			{
				while (len < (side_dist_y * tile_size))
				{
					mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_p->img,
						(data->player->pos_x * tile_size) + ray_dir_x * len,
						(data->player->pos_y * tile_size) + ray_dir_y * len);
					len++;
				}
				side_dist_y += delta_dist_y;
				map_y += step_y;
			}
			if (data->map->map[map_y][map_x] == '1')
				hit = 1;
		}
		x++;
	}
	len = -tile_size;
	while (len < tile_size)
	{
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->v_plane->img,
			(data->player->pos_x * tile_size) + (data->player->dir_x * tile_size) + data->player->plane_x * len,
			(data->player->pos_y * tile_size) + (data->player->dir_y * tile_size) + data->player->plane_y * len);
		len++;
	}
}

//fait tout le travail du raycasting pour une frame complète : 
//elle transforme la position et l'orientation du joueur en une image 3D, 
//colonne par colonne.
void    map_d_render(t_data *data)
{
	int x;
	int y;
	//vider entièrement le buffer - remet tous les pixels a 0;
	ft_memset(data->screen->addr, 0, data->screen->line_length * 1080);
	y = 0;
	x = 0;
	//récupère dans des variables locales (dir_x, dir_y, plane_x, plane_y)
	
	while (x < 1920)
	{
		//Pour chaque x : elle calcule camera_x (la position normalisée de cette colonne entre -1 et 1)
		data->ray->camera_x = 2.0 * x / 1920 - 1;
		//ray_dir_x/ray_dir_y (la direction du rayon envoyé pour cette colonne précise, 
		//en combinant dir et plane pondérés par camera_x)
		data->ray->ray_dir_x = data->player->dir_x + data->player->plane_x * data->ray->camera_x;
		data->ray->ray_dir_y = data->player->dir_y + data->player->plane_y * data->ray->camera_x;
		//map_x/map_y à la position actuelle du joueur
		data->ray->map_x = (int)data->player->pos_x;
		data->ray->map_y = (int)data->player->pos_y;
		//delta_dist_x/delta_dist_y la longueur de ce rayon spécifique avancer de 1.
		data->ray->delta_dist_x = (data->ray->ray_dir_x == 0) ? 1e30 : fabs(1 / data->ray->ray_dir_x);
		data->ray->delta_dist_y = (data->ray->ray_dir_y == 0) ? 1e30 : fabs(1 / data->ray->ray_dir_y);
		//l'initialisation du DDA : selon le signe de ray_dir_x/ray_dir_y, 
		//elle détermine step_x/step_y (la direction dans laquelle on avance dans la grille) et 
		//les side_dist_x/side_dist_y de départ 
		//(la distance jusqu'à la première ligne de grille rencontrée dans chaque axe)
		if (data->ray->ray_dir_x < 0)
		{
			data->ray->step_x = -1;
			data->ray->side_dist_x = (data->player->pos_x - (double)data->ray->map_x) * data->ray->delta_dist_x;
		}
		else
		{
			data->ray->step_x = 1;
			data->ray->side_dist_x = ((double)data->ray->map_x + 1.0 - data->player->pos_x) * data->ray->delta_dist_x;
		}
		if (data->ray->ray_dir_y < 0)
		{
			data->ray->step_y = -1;
			data->ray->side_dist_y = (data->player->pos_y - (double)data->ray->map_y) * data->ray->delta_dist_y;
		}
		else
		{
			data->ray->step_y = 1;
			data->ray->side_dist_y = ((double)data->ray->map_y + 1.0 - data->player->pos_y) * data->ray->delta_dist_y;
		}
		//la boucle while (!hit) fait avancer le rayon case par case dans la grille : 
		//à chaque itération, elle compare side_dist_x et side_dist_y, avance sur l'axe le plus proche, 
		//met à jour map_x ou map_y, note quel côté a été touché (side), 
		//et vérifie si la nouvelle case est un mur ('1'). Dès qu'un mur est trouvé, la boucle s'arrête.
		data->ray->hit = 0;
		while (!data->ray->hit)
		{
			if (data->ray->side_dist_x < data->ray->side_dist_y)
			{
				data->ray->side_dist_x += data->ray->delta_dist_x;
				data->ray->map_x += data->ray->step_x;
				data->ray->side = 0;
			}
			else
			{
				data->ray->side_dist_y += data->ray->delta_dist_y;
				data->ray->map_y += data->ray->step_y;
				data->ray->side = 1;
			}
			if (data->map->map[data->ray->map_y][data->ray->map_x] == '1')
				data->ray->hit = 1;
		}
		//Une fois le mur localisé, elle calcule perp_wall_dist — 
		//la distance perpendiculaire, en fonction de si le mur touché 
		//est un côté vertical (side == 0, formule avec side_dist_x) ou 
		//horizontal (side == 1, formule avec side_dist_y). 
		//Cette distance donne directement line_height, 
		//la hauteur en pixels du mur à dessiner pour cette colonne — 
		//plus la distance est grande, plus line_height est petit.
		if (data->ray->side == 0)
			data->ray->perp_wall_dist = data->ray->side_dist_x - data->ray->delta_dist_x;
		else
			data->ray->perp_wall_dist = data->ray->side_dist_y - data->ray->delta_dist_y;
		data->ray->line_height = 1080 / data->ray->perp_wall_dist;
		//draw_start/draw_end centrent cette hauteur de mur verticalement sur l'écran (1080/2 étant le milieu), 
		//en la clampant pour ne jamais dessiner en dehors des limites de l'image (0 à 1079). 
		//La dernière petite boucle sur y remplit chaque pixel de cette portion de colonne avec une couleur unie
		data->ray->draw_start = -data->ray->line_height / 2 + 1080 / 2;
		data->ray->draw_end = data->ray->line_height / 2 + 1080 / 2;
		if (data->ray->draw_start < 0) data->ray->draw_start = 0;
		if (data->ray->draw_end >= 1080) data->ray->draw_end = 1080 - 1;
		texture_mapping_x(data);
		y = 0;
		while (y < 1080)
		{
			if (y >= data->ray->draw_start && y <= data->ray->draw_end)
			{
				texture_mapping_y_draw(data, x, y);
			}
			else if (y < (1080 / 2))
				my_mlx_pixel_put(data->screen, x, y, data->map->color_f);
			else
				my_mlx_pixel_put(data->screen, x, y, data->map->color_c);
			y++;
		}
		x++;
	}
	//Une fois les 1920 colonnes traitées, un seul mlx_put_image_to_window affiche le buffer entier d'un coup
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->screen->img, 0, 0);
}     
