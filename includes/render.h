#ifndef RENDER_H
# define RENDER_H
# include <mlx.h>
# include "cub3d.h"
# include "libft.h"

void    my_mlx_pixel_put(t_img *img, int x, int y, int color);
void    draw_squar(void *img, int size, int color);
void    map_render(t_data *data);
void    map_d_render(t_data *data);

#endif
