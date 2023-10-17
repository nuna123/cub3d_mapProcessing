/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vert_dist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:09:58 by nroth             #+#    #+#             */
/*   Updated: 2023/10/16 13:10:00 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/*
	In case when angle == 0 or 180 we return 0 because it means ray will not hit
		vertical lines
	pl[2] - PLAYER XY - reset to player center
	dot[2] - FIRST INTERSECTION XY

	diff[0] is how much to add to the dot[0] pos in each loop - the x difference
	diff[1] is how much to add to the dot[1] pos in each loop == TEXTURE_SIZE

	dis_diff - first value is the hypoteneuse of player to the nearest check point
	dis is actual distance to the wall

	!!! dtr is Degrees To Radians function !!!
*/

static void	vert_init(t_gameInfo *gi, double a, double pl[2], double dot[2])
{
	pl[0] = (double) gi->player->x + floor(PLAYER_SIZE / 2);
	pl[1] = (double) gi->player->y + floor(PLAYER_SIZE / 2);
	dot[1] = (((int)(pl[1] / TEXTURE_SIZE) + (a > 180))) * TEXTURE_SIZE;
	dot[0] = pl[0] + ((a != 90 && a != 270) * ((pl[1] - dot[1]) / tan(dtr(a))));
}

int	get_vert_dist(t_gameInfo *gi, double a)
{
	double	pl[2];
	double	dot[2];
	double	diff[2];
	double	dis_diff;
	double	dis;

	if (a == 0 || a == 180)
		return (INT_MAX);
	vert_init(gi, a, pl, dot);
	dis_diff = fabs((TEXTURE_SIZE / sin(dtr(a))));
	diff[0] = dis_diff * cos (dtr(a));
	dis = fabs((fabs(pl[1] - dot[1]) / sin(dtr(180 - a))));
	diff[1] = TEXTURE_SIZE - (a < 180) * TEXTURE_SIZE * 2;
	while (dot[0] < WIDTH && dot[0] > 0 && dot[1] > 0 && dot[1] < HEIGHT)
	{
		if (coors_in_map (gi, dot[0] - (((int)round(dot[0]) % TEXTURE_SIZE == 0)
					&& (a > 90 && a < 270)),
				dot[1] - (a < 180)) != '0')
			return ((int)round(dis));
		dot[0] += diff[0];
		dot[1] += diff[1];
		dis += dis_diff;
	}
	return ((int)round(dis));
}
