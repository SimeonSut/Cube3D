/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 21:13:13 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/01 16:56:44 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <mlx.h>

# define FOV M_PI_4
# define W 1920
# define H 1080
# define ESC 65307
# define ROTATION_SPEED 0.00015
# define MOV_SPEED 0.08
# define XK_RIGHT 65363
# define XK_LEFT 65361

typedef struct s_texture
{
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		texture_x;
	int		texture_y;
	double	texture_pos;
	double	step;
	int		pixel_color;
}			t_texture;

typedef struct s_ray
{
	double	camera_x;
	double	rdx;
	double	rdy;
	int		map_x;
	int		map_y;
	double	ddx;
	double	ddy;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
}			t_ray;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_minimap
{
	t_img	*mm;
	t_img	*mp;
	t_img	*mw;
	int		wrat;
	int		hrat;
}			t_minimap;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dx;
	double	dy;
	double	plx;
	double	ply;
	int		player_nb;
}			t_player;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	char	*texture_no;
	char	*texture_so;
	char	*texture_we;
	char	*texture_ea;
	int		color_f;
	int		color_c;
}			t_map;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_player	p;
	t_map		*map;
	t_img		*screen;
	t_ray		*ray;
	t_texture	texture[4];
	int			tex_index;
	t_minimap	*mmap;
}				t_data;

#endif