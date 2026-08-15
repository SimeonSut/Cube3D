#include "parser.h"
#include "render.h"

//119 w
//115 s
//97 a
//100 d

void    movements(t_data *data, double x, double y)
{
    data->player.pos_x += x;
    data->player.pos_y += y;
}

int key_config(int keycode, void *param)
{
    t_data  *data;
    double  old_dir_x;
    double  old_plane_x;

    data = param;
    if (keycode == 'w')
        movements(data, 0, -0.05);
    else if (keycode == 's')
        movements(data, 0, 0.05);
    else if (keycode == 'a')
        movements(data, -0.05, 0);
    else if (keycode == 'd')
        movements(data, 0.05, 0);
    else if (keycode == 'q')
    {
        old_dir_x = data->player.dir_x;
        data->player.dir_x = data->player.dir_x * cos(-0.03) - data->player.dir_y * sin(-0.03);
        data->player.dir_y = old_dir_x * sin(-0.03) + data->player.dir_y * cos(-0.03);
        old_plane_x = data->player.plane_x;
        data->player.plane_x = data->player.plane_x * cos(-0.03) - data->player.plane_y * sin(-0.03);
        data->player.plane_y = old_plane_x * sin(-0.03) + data->player.plane_y * cos(-0.03);
    }
    else if (keycode == 'e')
    {
        old_dir_x = data->player.dir_x;
        data->player.dir_x = data->player.dir_x * cos(0.03) - data->player.dir_y * sin(0.03);
        data->player.dir_y = old_dir_x * sin(0.03) + data->player.dir_y * cos(0.03);
        old_plane_x = data->player.plane_x;
        data->player.plane_x = data->player.plane_x * cos(0.03) - data->player.plane_y * sin(0.03);
        data->player.plane_y = old_plane_x * sin(0.03) + data->player.plane_y * cos(0.03);
    }
    //map_render(data);
    map_d_render(data);
    return (0);
}

int main(int ac, char **av)
{
    t_data  data;
    char    **map_info;

    if (ac != 2)
    {
        ft_putstr_fd("Expected a file .cub\n", 2);
        return (0);
    }
    //get map info and init data
    map_info = map_info_parser(av[1]);
    if (!map_info)
        return (0);
    if (map_data_init(&data, map_info) != 0)
    {
        ft_putstr_fd("Map parsing failed !\n", 2);
        free_all(map_info);
        free_t_map(data.map);
        return (0);
    }
    free_all(map_info);
    // init player data
    if (player_data_init(&data) == 1)
    {
        ft_putstr_fd("Player init error\n", 2);
        free_t_map(data.map);
        return (0);
    }
    map_info = dup_map(data.map.map);
    if (flood_fill(map_info, data.player.pos_x, data.player.pos_y) == 1)
    {
        ft_putstr_fd("Map invalid: Player is not surround by wall !\n", 2);
        free_all(map_info);
        free_t_map(data.map);
        return (0);
    }
    free_all(map_info);
    // init mlx data
    data.mlx = mlx_init();
    if (!data.mlx)
    {
        ft_putstr_fd("mlx init failed\n", 2);
        free_t_map(data.map);
        return (0);
    }
    data.mlx_win = mlx_new_window(data.mlx, 1920, 1080, "TMP_TEST");
    if (!data.mlx_win)
    {
        ft_putstr_fd("new window fail\n",2);
        free_t_map(data.map);
        return (0);
    }
    // create a squar 64
    data.img.img = mlx_new_image(data.mlx, 64, 64);
    data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel,
        &data.img.line_length, &data.img.endian);
    draw_squar(&data.img, 64, 0x13031990);
    // create a player 
    data.img_p.img = mlx_new_image(data.mlx, 32, 32);
    data.img_p.addr = mlx_get_data_addr(data.img_p.img, &data.img_p.bits_per_pixel,
        &data.img_p.line_length, &data.img_p.endian);
    draw_squar(&data.img_p, 32, 0x00FF0000);
    // map render 2D
    //map_render(&data);

    // map render 3D
    data.screen.img = mlx_new_image(data.mlx, 1920, 1080);
    data.screen.addr = mlx_get_data_addr(data.screen.img, &data.screen.bits_per_pixel,
        &data.screen.line_length, &data.screen.endian);
    map_d_render(&data);
    //map_render(&data); 
    // key hook
    mlx_hook(data.mlx_win, 2, 1L<<0, (int (*)())(void *)key_config, &data);
    mlx_loop(data.mlx);
    return (0);
}
