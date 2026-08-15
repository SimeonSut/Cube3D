#include "render.h"

void    my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    draw_squar(void *img, int size, int color)
{
    int y;
    int x;

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

void    map_render(t_data *data)
{
    int y;
    int x;

    mlx_clear_window(data->mlx, data->mlx_win);
    y = 0;
    while (data->map.map[y])
    {
        x = 0;
        while (data->map.map[y][x])
        {
            if (data->map.map[y][x] == '1')
                mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img,
                    x * 64, y * 64);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_p.img,
        data->player.pos_x * 64, data->player.pos_y * 64);
}

//fait tout le travail du raycasting pour une frame complète : 
//elle transforme la position et l'orientation du joueur en une image 3D, 
//colonne par colonne.
void    map_d_render(t_data *data)
{
    int x;
    int y;
    //vider entièrement le buffer - remet tous les pixels a 0;
    ft_memset(data->screen.addr, 0, data->screen.line_length * 1080);
    y = 0;
    x = 0;
    //récupère dans des variables locales (dir_x, dir_y, plane_x, plane_y)
    double  dir_x = data->player.dir_x;
    double  dir_y = data->player.dir_y;
    double  plane_x = data->player.plane_x;
    double  plane_y = data->player.plane_y;
    //Pour chaque x : elle calcule camera_x (la position normalisée de cette colonne entre -1 et 1)
    double  camera_x = 2.0 * x / 1920 - 1;
    //ray_dir_x/ray_dir_y (la direction du rayon envoyé pour cette colonne précise, 
    //en combinant dir et plane pondérés par camera_x)
    double  ray_dir_x = dir_x + plane_x * camera_x;
    double  ray_dir_y = dir_y + plane_y * camera_x;
    //map_x/map_y à la position actuelle du joueur
    int     map_x = (int)data->player.pos_x;
    int     map_y = (int)data->player.pos_y;
    //delta_dist_x/delta_dist_y pour ce rayon spécifique.
    double  delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
    double  delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
    //l'initialisation du DDA : selon le signe de ray_dir_x/ray_dir_y, 
    //elle détermine step_x/step_y (la direction dans laquelle on avance dans la grille) et 
    //les side_dist_x/side_dist_y de départ (la distance jusqu'à la première ligne de grille rencontrée dans chaque axe)
    double  side_dist_x;
    double  side_dist_y;
    int     step_x;
    int     step_y;
    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (data->player.pos_x - (double)map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = ((double)map_x + 1.0 - data->player.pos_x) * delta_dist_x;
    }
    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (data->player.pos_y - (double)map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = ((double)map_y + 1.0 - data->player.pos_y) * delta_dist_y;
    }
    //la boucle while (!hit) fait avancer le rayon case par case dans la grille : 
    //à chaque itération, elle compare side_dist_x et side_dist_y, avance sur l'axe le plus proche, 
    //met à jour map_x ou map_y, note quel côté a été touché (side), 
    //et vérifie si la nouvelle case est un mur ('1'). Dès qu'un mur est trouvé, la boucle s'arrête.
    int side;
    int hit = 0;
    while (!hit)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }
        if (data->map.map[map_y][map_x] == '1')
            hit = 1;
    }
    //Une fois le mur localisé, elle calcule perp_wall_dist — 
    //la distance perpendiculaire, en fonction de si le mur touché 
    //est un côté vertical (side == 0, formule avec side_dist_x) ou 
    //horizontal (side == 1, formule avec side_dist_y). 
    //Cette distance donne directement line_height, 
    //la hauteur en pixels du mur à dessiner pour cette colonne — 
    //plus la distance est grande, plus line_height est petit.
    double  perp_wall_dist;
    if (side == 0)
        perp_wall_dist = side_dist_x - delta_dist_x;
    else
        perp_wall_dist = side_dist_y - delta_dist_y;
    int     line_height = 1080 / perp_wall_dist;
    printf("dirX = %f\n"
            "dirY = %f\n"
            "planeX = %f\n"
            "planeY = %f\n"
            "cameraX = %f\n"
            "rayDirX = %f\n"
            "rayDirY = %f\n"
            "mapX = %d\n"
            "mapY = %d\n"
            "deltaDistX = %f\n"
            "deltaDistY = %f\n"
            "sideDistX = %f\n"
            "sideDistY = %f\n"
            "stepX = %d\n"
            "stepY = %d\n"
            "perpWallDist = %f\n"
            "lineHeight = %d\n\r",
        dir_x, dir_y, plane_x, plane_y, camera_x, ray_dir_x, ray_dir_y,
        map_x, map_y, delta_dist_x, delta_dist_y, side_dist_x, side_dist_y,
        step_x, step_y, perp_wall_dist, line_height);
    
    x = 0;
    while (x < 1920)
    {
        camera_x = 2.0 * x / 1920 - 1;
        ray_dir_x = dir_x + plane_x * camera_x;
        ray_dir_y = dir_y + plane_y * camera_x;
        map_x = (int)data->player.pos_x;
        map_y = (int)data->player.pos_y;
        delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
        delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (data->player.pos_x - (double)map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = ((double)map_x + 1.0 - data->player.pos_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (data->player.pos_y - (double)map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = ((double)map_y + 1.0 - data->player.pos_y) * delta_dist_y;
        }
        hit = 0;
        while (!hit)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (data->map.map[map_y][map_x] == '1')
                hit = 1;
        }
        if (side == 0)
            perp_wall_dist = side_dist_x - delta_dist_x;
        else
            perp_wall_dist = side_dist_y - delta_dist_y;
        line_height = 1080 / perp_wall_dist;
        //draw_start/draw_end centrent cette hauteur de mur verticalement sur l'écran (1080/2 étant le milieu), 
        //en la clampant pour ne jamais dessiner en dehors des limites de l'image (0 à 1079). 
        //La dernière petite boucle sur y remplit chaque pixel de cette portion de colonne avec une couleur unie
        int draw_start = -line_height / 2 + 1080 / 2;
        int draw_end = line_height / 2 + 1080 / 2;
        if (draw_start < 0) draw_start = 0;
        if (draw_end >= 1080) draw_end = 1080 - 1;
        int color = 0x13031990;
        if (side == 1)
            color = color / 2;
        y = draw_start;
        while (y <= draw_end)
        {
            my_mlx_pixel_put(&data->screen, x, y, color);
            y++;
        }
        x++;
    }
    //Une fois les 1920 colonnes traitées, un seul mlx_put_image_to_window affiche le buffer entier d'un coup
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->screen.img, 0, 0);
}
