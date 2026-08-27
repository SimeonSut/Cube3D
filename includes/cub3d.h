/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 21:13:13 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/27 04:33:04 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <mlx.h>

# define FOV M_PI / 4

typedef struct s_texture
{
    void    *img;
    int     width;
    int     height;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     texture_x;
    int     texture_y;
    double  texture_pos;
    double  step;
    int     pixel_color;
}           t_texture;

typedef struct s_ray
{
    double  camera_x;
    double  ray_dir_x;
    double  ray_dir_y;
    int     map_x;
    int     map_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  side_dist_x;
    double  side_dist_y;
    int     step_x;
    int     step_y;
    int     side;
    int     hit;
    double  perp_wall_dist;
    int     line_height;
    int     draw_start;
    int     draw_end;
    double  wall_x;
}           t_ray;

typedef struct s_img
{
	void    *img;
	char    *addr;
	int     bits_per_pixel;
	int     line_length;
	int     endian;
}           t_img;

typedef struct s_minimap
{
    t_img   *mm;
    t_img   *mp;
    t_img   *mw;
}           t_minimap;

typedef struct s_player
{
	//double (pas int — le joueur doit pouvoir être à une position fractionnaire dans une case,
	//indispensable pour le mouvement fluide et le raycasting)
	double  pos_x;
	double  pos_y;
	//dir (dirX, dirY) : le vecteur qui pointe dans la direction où regarde le joueur.
	//plane (planeX, planeY) : le "plan de caméra", perpendiculaire à dir, qui définit
	//le champ de vision (FOV). C'est ce vecteur qui te permettra plus tard de balayer
	//tous les rayons de l'écran gauche à droite

	//vecteur direction
	double  dir_x;
	double  dir_y;
	//vecteur plan camera
	double  plane_x;
	double  plane_y;
	int     player_nb;
}           t_player;

typedef struct s_map
{
	char    **map;
	int     width;
	int     height;
	char    *texture_no;
	char    *texture_so;
	char    *texture_we;
	char    *texture_ea;
	int     color_f;
	int     color_c;
}           t_map;

typedef struct s_data
{
    void        *mlx;
    void        *mlx_win;
    t_player    *player;
    t_map       *map;
    t_img       *img;
    t_img       *img_p;
    t_img       *grill;
    t_img       *v_dir;
    t_img       *v_plane;
    t_img       *screen;
    t_ray       *ray;
    t_texture   texture[4];
    int         tex_index;
    t_minimap   *mmap;
}               t_data;

# define MOV_SPEED 0.05

#endif
