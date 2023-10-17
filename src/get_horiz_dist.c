/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_horiz_dist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:28:40 by nroth             #+#    #+#             */
/*   Updated: 2023/10/17 14:28:41 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	horiz_init(t_gameInfo *gi, double a, double pl[2], double dot[2])
{
	pl[0] = gi->player->x + floor(PLAYER_SIZE / 2);
	pl[1] = gi->player->y + floor(PLAYER_SIZE / 2);
	dot[0] = (((int)(pl[0] / TEXTURE_SIZE))
			+ (a < 90 || a > 270)) * TEXTURE_SIZE;
	dot[1] = pl[1] - ((dot[0] - pl[0]) * tan(dtr(a)));
}

int	get_horiz_dist(t_gameInfo *gi, double a)
{
	double	pl[2];
	double	dot[2];
	double	diff[2];
	double	dis_diff;
	double	dis;

	if (a == 90 || a == 270)
		return (INT_MAX);
	horiz_init(gi, a, pl, dot);
	dis_diff = fabs(TEXTURE_SIZE / cos(dtr(a)));
	dis = abs((int)((pl[0] - dot[0]) / cos(dtr(a))));
	diff[1] = -1 * sin(dtr(a)) * dis_diff;
	diff[0] = TEXTURE_SIZE - (((a > 90 && a < 270)) * TEXTURE_SIZE * 2);
	while (dot[0] < WIDTH && dot[0] > 0 && dot[1] > 0 && dot[1] < HEIGHT)
	{
		if (coors_in_map(gi, dot[0] - (a > 90 && a < 270),
				dot[1] - (((int) round (dot[1]) % TEXTURE_SIZE == 0)
					&& (a < 180))) != '0')
			return ((int) round(dis));
		dot[0] += diff[0];
		dot[1] += diff[1];
		dis += dis_diff;
	}
	return ((int) round(dis));
}
