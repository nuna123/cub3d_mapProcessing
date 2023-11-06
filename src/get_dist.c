/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:28:40 by nroth             #+#    #+#             */
/*   Updated: 2023/10/27 10:58:16 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	horiz_init(t_gameInfo *gi, double a, double pl[2], double dot[2])
{
	pl[0] = gi->player->x + floor(gi->player_size / 2);
	pl[1] = gi->player->y + floor(gi->player_size / 2);
	dot[0] = (((int)(pl[0] / gi->txtr_size))
			+ (a < 90 || a > 270)) * gi->txtr_size;
	dot[1] = pl[1] - ((dot[0] - pl[0]) * tan(dtr(a)));
}

static double	get_horiz_dist(t_gameInfo *gi, double a)
{
	double	pl[2];
	double	dot[2];
	double	diff[2];
	double	dis_diff;
	double	dis;

	if (a == 90 || a == 270)
		return (-1);
	horiz_init(gi, a, pl, dot);
	dis_diff = fabs(gi->txtr_size / cos(dtr(a)));
	dis = fabs(((pl[0] - dot[0]) / cos(dtr(a))));
	diff[1] = -1 * sin(dtr(a)) * dis_diff;
	diff[0] = gi->txtr_size - (((a > 90 && a < 270)) * gi->txtr_size * 2);
	while (dot[0] < gi->screen_w && dot[0] > 0
		&& dot[1] > 0 && dot[1] < gi->screen_h)
	{
		if (coors_in_map(gi, dot[0] - (a > 90 && a < 270), dot[1] - (
					(fmod(dot[1], gi->txtr_size) == 0) && (a < 180))) != '0')
			break ;
		dot[0] += diff[0];
		dot[1] += diff[1];
		dis += dis_diff;
	}
	return (dis);
}
/*
	In case when angle == 0 or 180 we return 0 because it means ray will not hit
		vertical lines
	pl[2] - PLAYER XY - reset to player center
	dot[2] - FIRST INTERSECTION XY

	diff[0] is how much to add to the dot[0] pos in each loop - the x difference
	diff[1] is how much to add to the dot[1] pos in each loop == gi->txtr_size

	dis_diff - first value is the hypoteneuse of player to the nearest check point
	dis is actual distance to the wall

	!!! dtr is Degrees To Radians function !!!
*/

static void	vert_init(t_gameInfo *gi, double a, double pl[2], double dot[2])
{
	pl[0] = (double) gi->player->x + floor(gi->player_size / 2);
	pl[1] = (double) gi->player->y + floor(gi->player_size / 2);
	dot[1] = (((int)(pl[1] / gi->txtr_size) + (a > 180))) * gi->txtr_size;
	dot[0] = pl[0] + ((a != 90 && a != 270) * ((pl[1] - dot[1]) / tan(dtr(a))));
}

static double	get_vert_dist(t_gameInfo *gi, double a)
{
	double	pl[2];
	double	dot[2];
	double	diff[2];
	double	dis_diff;
	double	dis;

	if (a == 0 || a == 180)
		return (-1);
	vert_init(gi, a, pl, dot);
	dis_diff = fabs((gi->txtr_size / sin(dtr(a))));
	diff[0] = dis_diff * cos (dtr(a));
	dis = fabs((fabs(pl[1] - dot[1]) / sin(dtr(180 - a))));
	diff[1] = gi->txtr_size - (a < 180) * gi->txtr_size * 2;
	while (dot[0] < gi->screen_w && dot[0] > 0
		&& dot[1] > 0 && dot[1] < gi->screen_h)
	{
		if (coors_in_map (gi, dot[0] - ((fmod(dot[0], gi->txtr_size) == 0)
					&& (a > 90 && a < 270)), dot[1] - (a < 180)) != '0')
			break ;
		dot[0] += diff[0];
		dot[1] += diff[1];
		dis += dis_diff;
	}
	return (dis);
}

double	get_dist(t_gameInfo *gi, double angle, int *txtr)
{
	float			vert_dis;
	float			horiz_dis;
	double			corr_ang;

	if (angle < 360)
		corr_ang = (fmod((angle + 360), 360) - gi->player->angle);
	else
		corr_ang = (angle - gi->player->angle);
	horiz_dis = (float)get_horiz_dist(gi, fmod((angle + 360), 360));
	vert_dis = (float)get_vert_dist(gi, fmod((angle + 360), 360));
	define_texture(horiz_dis, vert_dis, angle, txtr);
	if (vert_dis == -1)
		return (horiz_dis * cos(dtr(corr_ang)));
	if (horiz_dis == -1)
		return (vert_dis * cos(dtr(corr_ang)));
	if (horiz_dis <= vert_dis)
		return (horiz_dis * cos(dtr(corr_ang)));
	return (vert_dis * cos(dtr(corr_ang)));
}
