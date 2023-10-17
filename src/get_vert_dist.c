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
int	get_vert_dist(t_gameInfo	*gi, double a)
{
	double	pl[2];
	double	dot[2];
	double	diff[2];

	double	dis_diff;
	double	dis;

	if (a == 0 || a == 180)
		return (INT_MAX);
	pl[0] = (double) gi->player->x + floor(PLAYER_SIZE / 2);
	pl[1] = (double) gi->player->y + floor(PLAYER_SIZE / 2);
	dot[1] = (((int) (pl[1] / TEXTURE_SIZE) + (a > 180))) * TEXTURE_SIZE;
	dot[0] = pl[0] + (a != 90 && a != 270) * ((pl[1] - dot[1]) / tan(dtr(a)));
	dis_diff = fabs((TEXTURE_SIZE / sin(dtr(a))));
		printf("\n\nPLAYER XY = %f, %f\n", pl[0], pl[1]);
		printf("dis diff %f\n", dis_diff);


	diff[0] = dis_diff * cos (dtr(a));
	dis = fabs((fabs(pl[1] - dot[1]) / sin(dtr(180 - a))));
	diff[1] = TEXTURE_SIZE - (a < 180) * TEXTURE_SIZE * 2;
	while (dot[0] < WIDTH && dot[0] > 0 && dot[1] > 0 && dot[1] < HEIGHT)
	{
		dprintf(FD, "\n%sB(XY): %f, %f%s\n",CYN, dot[0], dot[1], WHT);

		if (coors_in_map(gi, dot[0] - (((int)round (dot[0]) % TEXTURE_SIZE == 0)&&(a > 90 && a < 270)),
			dot[1] - (((int)round (dot[1]) % TEXTURE_SIZE == 0)&&(a < 180))) != '0')
		{
			printf("%sfinal xy: %f, %f\n%s",CYN, dot[0], dot[1], WHT);
			printf("%sfinal dis: %f\n%s",CYN, dis, WHT);

			// mark_pnt(gi, dot[0], dot[1], 0x00FF00FF);
			return ((int) ceil(dis));
		}
/* 		if (coors_in_map(gi, dot[0], dot[1] - (a < 180)) != '0')
			return (dis); */
/* 		if (coors_in_map(gi, dot[0], dot[1]) != '0')
			return (dis); */
		dot[0] += diff[0];
		dot[1] += diff[1];
		dis += dis_diff;
		printf("dis %f\n", dis);
	}
	return ((int) ceil(dis));
}

/* double get_vert_dist(t_gameInfo	*gi, double a)
{
	if (a == 0 || a == 180)
		return 0;
int U_D;

int pl[2];
int dot[2]

double diff[0];
int	diff[1];

double dis_diff;
double	dis;

	U_D = 1 - (a < 180);

	//pl XY
	pl[0] = gi->pl->x + floor(PLAYER_SIZE / 2);
	pl[1] = gi->pl->y + floor(PLAYER_SIZE / 2);


	//FIRST INTERSECTION XY


	dot[1] = ((int)(pl[1] / TEXTURE_SIZE + U_D)) * TEXTURE_SIZE;
	dot[0] = pl[0] + (a != 90 && a != 270) * ((pl[1] - dot[1]) / tan(dtr(a)));

	dis_diff = abs(TEXTURE_SIZE / sin(dtr(a)));

	//how much to add to the x pos in each loop
	diff[0] = dis_diff * cos (dtr(a));
	dis = abs(abs(pl[1] - dot[1]) / sin(dtr(180 - a)));
	diff[1] = TEXTURE_SIZE - (U_D == 0) * TEXTURE_SIZE * 2;

	while (dot[0] < WIDTH && dot[0] > 0 && dot[1] > 0 && dot[1] < HEIGHT)
	{
		// mark_pnt(gi, dot[0], dot[1], 0xFF00FFFF);
		if (coors_in_map(gi, dot[0] , dot[1] - (U_D == 0)) == '1')
			return (abs(dis));
		dot[0] += diff[0];
		dot[1] += diff[1];
		dis += dis_diff;
	}
	return (abs(dis));
} */
