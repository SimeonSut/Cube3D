#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}           t_img;

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
    t_player    player;
    t_map       map;
    t_img       img;
    t_img       img_p;
    t_img       screen;
}               t_data;

#endif
