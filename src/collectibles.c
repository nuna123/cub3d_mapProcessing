/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:41:18 by ymorozov          #+#    #+#             */
/*   Updated: 2023/11/10 18:25:13 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

char	obj_xy_inmap(t_gameInfo *gi, int x, int y, int *id)
{
	if (x < 0 || y < 0)
		return (printf("1ERR! %i, %i\n", x, y), -1);
	if (y / gi->txtr_size >= gi->map_info->map_height
		|| x / gi->txtr_size >= gi->map_info->map_width)
		return (printf("2ERR! %i, %i\n\n", x, y), -1);
	*id = ((y / gi->txtr_size) * gi->map_info->map_width) + (x / gi->txtr_size);
	return (gi->map_info->map
		[(y / gi->txtr_size)]
		[(x / gi->txtr_size)]);
}

t_star	*make_new_star(int x, int y, int width, int height)
{
	t_star	*new_star;

	new_star = ft_calloc(sizeof(t_star), 1);
	if (!new_star)
		return (NULL);
	new_star->x = x;
	new_star->y = y;
	new_star->width = width;
	new_star->height = height;
	return (new_star);
}
