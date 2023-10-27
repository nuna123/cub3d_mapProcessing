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
	pl[0] = gi->player->x + floor(PLAYER_SIZE / 2);
	pl[1] = gi->player->y + floor(PLAYER_SIZE / 2);
	dot[0] = (((int)(pl[0] / TEXTURE_SIZE))
			+ (a < 90 || a > 270)) * TEXTURE_SIZE;
	dot[1] = pl[1] - ((dot[0] - pl[0]) * tan(dtr(a)));
}

// double	get_horiz_dist(t_gameInfo *gi, double a,  FILE ** fp)
double	get_horiz_dist(t_gameInfo *gi, double a)
{
	double	pl[2];
	double	dot[2];
	double	diff[2];
	double	dis_diff;
	double	dis;

	if (a == 90 || a == 270)
		return (-1);
	horiz_init(gi, a, pl, dot);
	dis_diff = fabs(TEXTURE_SIZE / cos(dtr(a)));
	dis = fabs(((pl[0] - dot[0]) / cos(dtr(a))));
	diff[1] = -1 * sin(dtr(a)) * dis_diff;
	diff[0] = TEXTURE_SIZE - (((a > 90 && a < 270)) * TEXTURE_SIZE * 2);
	while (dot[0] < WIDTH && dot[0] > 0 && dot[1] > 0 && dot[1] < HEIGHT)
	{

		if (coors_in_map(gi, dot[0] - (a > 90 && a < 270),
				dot[1] - ( (fmod(dot[1], TEXTURE_SIZE) == 0) && (a < 180))) != '0')
			break;
		dot[0] += diff[0];
		dot[1] += diff[1];
		dis += dis_diff;
	}
		// fprintf(*fp, "	distance to return in get_horiz= %f;\n", dis);
	return (dis);
}
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

// double	get_vert_dist(t_gameInfo *gi, double a, FILE ** fp)
double	get_vert_dist(t_gameInfo *gi, double a)
{
	double	pl[2];
	double	dot[2];
	double	diff[2];
	double	dis_diff;
	double	dis;

	if (a == 0 || a == 180)
		return (-1);
	vert_init(gi, a, pl, dot);
	dis_diff = fabs((TEXTURE_SIZE / sin(dtr(a))));
	diff[0] = dis_diff * cos (dtr(a));
	dis = fabs((fabs(pl[1] - dot[1]) / sin(dtr(180 - a))));
	diff[1] = TEXTURE_SIZE - (a < 180) * TEXTURE_SIZE * 2;
	while (dot[0] < WIDTH && dot[0] > 0 && dot[1] > 0 && dot[1] < HEIGHT)
	{
		if (coors_in_map (gi, dot[0] - ((fmod(dot[0], TEXTURE_SIZE) == 0) && (a > 90 && a < 270)),
				dot[1] - (a < 180)) != '0')
			break;
		dot[0] += diff[0];
		dot[1] += diff[1];
		dis += dis_diff;
		// fprintf(*fp, "	new dot(%f, %f); dis = %f\n",dot[0], dot[1], dis);
	}
		// fprintf(*fp, "	distance to return in get_vert= %f;\n", dis);
	return (dis);
}

// double get_dist (t_gameInfo *gi, double angle, int *txtr)
double get_dist (t_gameInfo *gi, double angle, int *txtr, FILE ** fp)
{
	float		vert_dis;
	float		horiz_dis;
	double			corr_ang;
	double			new_ang;

new_ang = fmod((angle + 360), 360);
	if (angle < 360)
		corr_ang = (fmod((angle + 360), 360) - gi->player->orientation);
	else
		corr_ang = (angle - gi->player->orientation);
	horiz_dis = (float)get_horiz_dist(gi,fmod((angle + 360), 360));
	vert_dis = (float)get_vert_dist(gi,fmod((angle + 360), 360));
		fprintf(*fp, "HOR DIST: %f		VER DIST: %f\n", horiz_dis, vert_dis);
		fprintf(*fp, "first angle: %f, sec_angle: %f;corr_ang = %f, cos(cor) = %f;\n", angle,fmod((angle + 360), 360), corr_ang, cos(dtr(corr_ang)));


	if ((new_ang < 90 || new_ang > 270) && (vert_dis == -1 || horiz_dis < vert_dis))
		*txtr = 0;
	else if ((new_ang > 0 && new_ang < 180) && (horiz_dis == -1 || horiz_dis > vert_dis))
		*txtr = 1;
	else if ((new_ang > 90 && new_ang < 270) && (vert_dis == -1 || horiz_dis < vert_dis))
		*txtr = 2;
	else if ((new_ang >180 && new_ang < 360) && (horiz_dis == -1 || horiz_dis > vert_dis))
		*txtr = 3;

	if (vert_dis == -1)
		return (horiz_dis * cos(dtr(corr_ang)));
	if (horiz_dis == -1)
		return (vert_dis * cos(dtr(corr_ang)));
	if (horiz_dis <= vert_dis)
		return (horiz_dis * cos(dtr(corr_ang)));
	return (vert_dis * cos(dtr(corr_ang)));
}

/* if (((angle > -90 && angle < 0) || (angle > 360 && angle < 391)) && (horiz_dis <= vert_dis)) //1
	{
		*txtr = 0;
		fprintf(*fp, " case 1: txtr = 0, yellow\n");
		}
	else if (((angle > -90 && angle < 0) || (angle > 360 && angle < 391)) && (horiz_dis > vert_dis))//2
	{	*txtr = 1;
		fprintf(*fp, " case 2: txtr = 1, purple\n");
	}
	else if ((angle < 90 || (angle > 270 && angle < 360)) && (vert_dis == -1 || horiz_dis < vert_dis))//3
	{	*txtr = 0;
		fprintf(*fp, " case 3: txtr = 0, yellow\n");
	}
	else if ((angle < 90 || (angle > 270 && angle < 360)) && (horiz_dis == vert_dis))//4
	{
		//HEADACHE
		if (angle < 90)
			*txtr = 0;
		else
			*txtr = 3;
		fprintf(*fp, " case 4\n");
	}
	else if ((angle > 0 && angle < 180) && (horiz_dis == -1 || horiz_dis > vert_dis))//5
	{	*txtr = 1;
		fprintf(*fp, " case 5: txtr = 1, purple\n");
	}
	else if ((angle > 0 && angle < 180) && (horiz_dis == vert_dis))//6
	{	*txtr = 1;
		fprintf(*fp, " case 6: txtr = 1, purple\n");
	}
	else if ((angle > 90 && angle < 270) && (vert_dis == -1 || horiz_dis < vert_dis))//7
	{	*txtr = 2;
		fprintf(*fp, " case 7: txtr = 2, coral\n");
	}
	else if ((angle > 90 && angle < 270) && (horiz_dis == vert_dis))//8
	{	*txtr = 2;
		fprintf(*fp, " case 8: txtr = 2, coral\n");
	}
	else if ((angle >180 && angle < 360) && (horiz_dis == -1 || horiz_dis > vert_dis))//9
	{	*txtr = 3;
		fprintf(*fp, " case 9: txtr = 3, green\n");
	}
	else if ((angle >180 && angle < 360) && ( horiz_dis == vert_dis))//10 //TBD
	{	*txtr = 3;
		fprintf(*fp, " case 10: txtr = 3, green\n");
	}
	else {
		fprintf(*fp, " 	Something went wrong\n");
	} */