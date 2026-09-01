/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 21:13:54 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/01 18:40:38 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	t_data_init(t_data *new)
{
	new->mlx = NULL;
	new->mlx_win = NULL;
	new->map.map = NULL;
	new->map.texture_no = NULL;
	new->map.texture_so = NULL;
	new->map.texture_we = NULL;
	new->map.texture_ea = NULL;
	new->screen.img = NULL;
	new->texture[0].img = NULL;
	new->texture[1].img = NULL;
	new->texture[2].img = NULL;
	new->texture[3].img = NULL;
	new->mmap.mm.img = NULL;
	new->mmap.mp.img = NULL;
	new->mmap.mw.img = NULL;
}
