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

int	get_star_start(t_gameInfo *gi, int x, double *min_dis)
{
	int		star_start;
	int		old_block;
	int		block;
	double	dis;

	block = -1;
	old_block = -1;
	dis = WIDTH;
	star_start = x;
	while (dis != -1)
	{
		if (dis < *min_dis)
			*min_dis = dis;
		dis = star_get_dist(gi,
				gi->player->angle + (FOV / 2)
				- ((FOV / (double) WIDTH) * star_start) - gi->offset, &block);
		if ((block != old_block && old_block != -1) || dis == -1)
			break ;
		star_start--;
		old_block = block;
	}
	return (++star_start);
}

int	get_star_end(t_gameInfo *gi, int x, double *min_dis, t_star	***stars)
{
	int		star_end;
	int		old_block;
	int		block;
	double	dis;

	dis = WIDTH;
	star_end = x;
	old_block = -1;
	block = -1;
	while (dis != -1)
	{
		if (dis < *min_dis)
			*min_dis = dis;
		dis = star_get_dist(gi, gi->player->angle + (FOV / 2)
				- ((FOV / (double) WIDTH) * star_end) - gi->offset, &block);
		if ((block != old_block && old_block != -1) || (dis == -1))
		{
			printf("b: %i ;  old_b: %i;\n", block, old_block);
			if (dis > -1)
				get_star(gi, star_end, stars);
			break ;
		}
		old_block = block;
		star_end++;
	}
	return (--star_end);
}

void	get_star(t_gameInfo *gi, int x, t_star	***stars)
{
	int		star_start;
	int		star_end;
	double	min_dis;
	t_star	*new_star;

	min_dis = WIDTH;
	star_start = get_star_start(gi, x, &min_dis);
	star_end = get_star_end(gi, x, &min_dis, stars);
	star_start += ((star_end - star_start) - ((star_end - star_start) / 2)) / 2;
	min_dis = round(
			(32 * (WIDTH * 0.5 / tan(dtr(FOV / 2)))) / min_dis);
	new_star = make_new_star(star_start, ((HEIGHT - min_dis) / 2) + 50,
			((star_end - star_start) / 2), min_dis / 2);
	if (!new_star)
		return ;
	if (new_star->x > WIDTH || new_star->x + new_star->width <= 0)
		free(new_star);
	else if (new_star->y > HEIGHT
		||new_star->y + new_star->height <= 0
		|| new_star->width < 10)
		free(new_star);
	else
		*stars = (t_star **)ft_arrappend_void((void **)(*stars),
				(void *)new_star);
}
