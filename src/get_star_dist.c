/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_star_dist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:21:04 by ymorozov          #+#    #+#             */
/*   Updated: 2023/11/14 13:39:15 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	star_hor_init(t_gameInfo *gi, double a, double pl[2], double dot[2])
{
	pl[0] = gi->player->x + floor(gi->player_size / 2);
	pl[1] = gi->player->y + floor(gi->player_size / 2);
	dot[0] = (((int)(pl[0] / gi->txtr_size))
			+ (a < 90 || a > 270)) * gi->txtr_size;
	dot[0] += 8;
	dot[1] = pl[1] - ((dot[0] - pl[0]) * tan(dtr(a)));
}

//	h - horizontal block
//	d - distance

static double	star_get_h_dist(t_gameInfo *gi, double a, int *h)
{
	double	pl[2];
	double	dot[2];
	double	diff[2];
	double	dis_diff;
	double	d;

	if (a == 90 || a == 270)
		return (-1);
	star_hor_init(gi, a, pl, dot);
	dis_diff = fabs(gi->txtr_size / cos(dtr(a)));
	d = fabs(((pl[0] - dot[0]) / cos(dtr(a))));
	diff[1] = -1 * sin(dtr(a)) * dis_diff;
	diff[0] = gi->txtr_size - (((a > 90 && a < 270)) * gi->txtr_size * 2);
	while (dot[0] < (gi->map_info->map_width * gi->txtr_size) && dot[0] > 0
		&& dot[1] > 0 && dot[1] < (gi->map_info->map_height * gi->txtr_size))
	{
		if (coors_in_map(gi, dot[0] - (a > 90 && a < 270), dot[1] - (
					(fmod(dot[1], gi->txtr_size) == 0) && (a < 180))) == '1')
			return (-1);
					
		if (coors_in_map(gi, dot[0] - (a > 90 && a < 270), dot[1] - (
					(fmod(dot[1], gi->txtr_size) == 0) && (a < 180))) == 'C')
			return (obj_xy_inmap(gi, dot[0] - (a > 90 && a < 270), dot[1]
					- ((fmod(dot[1], gi->txtr_size) == 0) && (a < 180)), h), d);
		dot[0] += diff[0];
		dot[1] += diff[1];
		d += dis_diff;
	}
	return (-1);
}

static void	star_ver_init(t_gameInfo *gi, double a, double pl[2], double dot[2])
{
	pl[0] = (double) gi->player->x + floor(gi->player_size / 2);
	pl[1] = (double) gi->player->y + floor(gi->player_size / 2);
	dot[1] = (((int)(pl[1] / gi->txtr_size) + (a > 180))) * gi->txtr_size;
	dot[1] += 8;
	dot[0] = pl[0] + ((a != 90 && a != 270) * ((pl[1] - dot[1]) / tan(dtr(a))));
}

//	v_bl - vertical block
//	d[2] - dot coordinates ([0]- x [1] - y)

static double	star_get_v_dist(t_gameInfo *gi, double a, int *v_bl)
{
	double	pl[2];
	double	d[2];
	double	diff[2];
	double	dis_diff;
	double	dis;

	if (a == 0 || a == 180)
		return (-1);
	star_ver_init(gi, a, pl, d);
	dis_diff = fabs((gi->txtr_size / sin(dtr(a))));
	diff[0] = dis_diff * cos (dtr(a));
	dis = fabs((fabs(pl[1] - d[1]) / sin(dtr(180 - a))));
	diff[1] = gi->txtr_size - (a < 180) * gi->txtr_size * 2;
	while (d[0] < (gi->map_info->map_width * gi->txtr_size) && d[0] > 0
		&& d[1] > 0 && d[1] < (gi->map_info->map_height * gi->txtr_size))
	{
		if (coors_in_map (gi, d[0] - ((fmod(d[0], gi->txtr_size) == 0)
					&& (a > 90 && a < 270)), d[1] - (a < 180)) == '1')
			return -1;
		if (coors_in_map (gi, d[0] - ((fmod(d[0], gi->txtr_size) == 0)
					&& (a > 90 && a < 270)), d[1] - (a < 180)) == 'C')
			return (obj_xy_inmap (gi, d[0] - ((fmod(d[0], gi->txtr_size) == 0)
						&& (a > 90 && a < 270)), d[1] - (a < 180), v_bl), dis);
		d[0] += diff[0];
		d[1] += diff[1];
		dis += dis_diff;
	}
	return (-1);
}
//dis	[0] = vertical distance to the nearest star,
//		[1] = horizotal distance to the nearest star,
//blocks[0] = block identifier of vertical check
//		[1] = block identifier of horizontal check

double	star_get_dist(t_gameInfo *gi, double angle, int *block)
{
	double	dis[2];
	double	wall_dis;
	double	corr_ang;
	int		blocks[0];
	int		txtr;

	if (angle < 360)
		corr_ang = (fmod((angle + 360), 360)
				- (gi->player->angle - gi->offset));
	else
		corr_ang = (angle - (gi->player->angle - gi->offset));
	dis[1] = star_get_h_dist(gi, fmod((angle + 360), 360), &blocks[1]);
	dis[0] = star_get_v_dist(gi, fmod((angle + 360), 360), &blocks[0]);
	wall_dis = get_dist(gi, angle, &txtr);
	
	printf("ang:%f		cor_ang: %f, hor = %f, vert = %f, wall = %f\n",fmod((angle + 360), 360),corr_ang, dis[1], dis[0], wall_dis);
	
	if (wall_dis < dis[1] && dis[0] == -1)
		return (-1);
	if (wall_dis < dis[0] && dis[1] == -1)
		return (-1);
	if (wall_dis < dis[0] && wall_dis < dis[1])
		return (-1);
		
	if (dis[0] == -1 && dis[1] == -1)
		return (-1);
	if (dis[0] == -1)
		return ((*block = blocks[1]), dis[1] * cos(dtr(corr_ang)));
	if (dis[1] == -1)
		return ((*block = blocks[0]), dis[0] * cos(dtr(corr_ang)));
	if (dis[1] <= dis[0])
		return ((*block = blocks[1]), dis[1] * cos(dtr(corr_ang)));
	return ((*block = blocks[0]), dis[0] * cos(dtr(corr_ang)));
}
