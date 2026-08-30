/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 21:13:54 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/30 12:54:22 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_map	*t_map_init(void);
static int		img_mem_init(t_data *new);

t_data	*t_data_init(void)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->mlx = NULL;
	new->mlx_win = NULL;
	new->player = malloc(sizeof(t_player));
	if (!new->player)
		return (free(new), NULL);
	new->map = t_map_init();
	if (!new->map)
		return (free_data(new), NULL);
	if (img_mem_init(new) == 1)
		return (free_data(new), NULL);
	if (!new->screen)
		return (free_data(new), NULL);
	return (new);
}

static t_map	*t_map_init(void)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->map = NULL;
	new->texture_no = NULL;
	new->texture_so = NULL;
	new->texture_we = NULL;
	new->texture_ea = NULL;
	return (new);
}

static int img_mem_init(t_data *new)
{
	new->img = malloc(sizeof(t_img));
	new->img_p = malloc(sizeof(t_img));
	if (!new->img || !new->img_p)
		return (1);
	new->grill = malloc(sizeof(t_img));
	if (!new->grill)
		return (1);
	new->v_dir = malloc(sizeof(t_img));
	new->v_plane = malloc(sizeof(t_img));
	if (!new->v_dir || !new->v_plane)
		return (1);
	new->screen = malloc(sizeof(t_img));
	new->ray = malloc(sizeof(t_ray));
	if (!new->screen || !new->ray)
		return (1);
	new->mmap = malloc(sizeof(t_minimap));
	new->mmap->mm = malloc(sizeof(t_img));
	new->mmap->mp = malloc(sizeof(t_img));
	new->mmap->mw = malloc(sizeof(t_img));
	if (!new->mmap || !new->mmap->mm || !new->mmap->mp || !new->mmap->mw)
		return (1);
	return (0);
}
