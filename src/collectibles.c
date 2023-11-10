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
	//ERROR HANDLING
	new_star->x = x;
	new_star->y = y;
	new_star->width = width;
	new_star->height = height;
	return (new_star);
}

void	get_star(t_gameInfo *gi, int x, t_star	***stars)
{
	int		star_start;
	int		star_end;
	int		old_block;
	int		block;
	double	dis;
	double	min_dis;
	t_star	*new_star;

	block = -1;
	old_block = -1;
	min_dis = WIDTH;
	dis = WIDTH;
	star_start = x;
	while (dis != -1)
	{
		if (dis < min_dis)
			min_dis = dis;
		dis = star_get_dist(gi,
				gi->player->angle + (FOV / 2)
				- ((FOV / (double) WIDTH) * star_start) - gi->offset, &block);
		if (block != old_block && old_block != -1)
			break ;
		star_start--;
		old_block = block;
	}
	star_start++;
	dis = WIDTH;
	star_end = x;
	old_block = -1;
	block = -1;
	while (dis != -1)
	{
		if (dis < min_dis)
			min_dis = dis;
		dis = star_get_dist(gi,
				gi->player->angle + (FOV / 2)
				- ((FOV / (double) WIDTH) * star_end) - gi->offset, &block);
		if (block != old_block && old_block != -1)
		{
			get_star(gi, star_end, stars);
			break ;
		}
		old_block = block;
		star_end++;
	}
	star_end--;
	star_start += ((star_end - star_start) - ((star_end - star_start) / 2)) / 2;
	min_dis = round(
			(32 * (WIDTH * 0.5 / tan(dtr(FOV / 2)))) / min_dis);
	new_star = make_new_star(star_start, ((HEIGHT - min_dis) / 2) + 50, ((star_end - star_start) / 2), min_dis / 2);
	if (new_star->x > WIDTH || new_star->x + new_star->width <= 0)
		free(new_star);
	else if (new_star->y > HEIGHT || new_star->y + new_star->height <= 0 || new_star->width < 10)
		free(new_star);
	else
		*stars = (t_star **)ft_arrappend_void((void **)(*stars), (void *)new_star);
}

t_star	**get_stars(t_gameInfo *gi)
{
	t_star	**stars;
	int		x;
	double	dis;
	double	star_c;
	int		unused;

	x = -1;
	stars = NULL;
	star_c = 0;
	while (++x < WIDTH)
	{
		dis = star_get_dist(gi,
				gi->player->angle + (FOV / 2)
				- ((FOV / (double) WIDTH) * x) - gi->offset, &unused);
		if ((star_c == -1 || star_c == 0) && dis != -1)
			get_star(gi, x, &stars);
		if (star_c != -1 && dis == -1)
			star_c = 0;
		star_c = dis;
	}
	return (stars);
}
