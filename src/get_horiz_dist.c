#include "game.h"

double get_horiz_dist(t_gameInfo	*gi, double angle)
{

	if (angle == 90 || angle == 270)
		return 0;
	int U_D = 1;
	if (angle < 180)
		U_D = 0;

	int L_R = 0;
	if (angle < 90 || angle > 270)
		L_R = 1;

	// printf("L_R: %i, UD = %i\n", L_R, U_D);

	//PLAYER XY
	int P_x = gi->player->x + (PLAYER_SIZE / 2);
	int P_y = gi->player->y + (PLAYER_SIZE / 2);

	//FIRST INTERSECTION XY
	int B_x;
	int B_y;

	if (L_R == 1) // RIGHT
		B_x = ((int)(P_x / TEXTURE_SIZE) + 1) * TEXTURE_SIZE;
	else
		B_x = ((int)(P_x / TEXTURE_SIZE)) * TEXTURE_SIZE;

	if (L_R == 1)
	{
		if (U_D == 0)
			B_y = P_y + (P_x-B_x) * tan(deg_to_rad(angle)); // top right
		else
			B_y = P_y - (P_x-B_x) * tan(deg_to_rad(360 - angle)); // bottom right
	}

	if (L_R == 0)
	{
		if (U_D == 0)
			B_y = P_y - (P_x-B_x) * tan(deg_to_rad(180 - angle)); // top left
		else
			B_y = P_y + (P_x-B_x) * tan(deg_to_rad(angle - 180)); // bottom left
	}
	//how much to add to the y pos in each loop
	double y_diff = TEXTURE_SIZE * tan (deg_to_rad(angle));
	if (angle == 45 || angle == 315)
		y_diff *= -1;


	//first value is the hypoteneuse of player to the nearest check point
	double dis_diff = fabs(TEXTURE_SIZE / cos(deg_to_rad(angle)));
			// printf("DIS diff: %f\n", dis_diff);
		//first value is the hypoteneuse of player to the nearest check point


double	dis;


	dis = abs(P_x - B_x) / fabs(cos(deg_to_rad(angle)));

/* 	printf("fabs : %d ", abs(P_y - B_y));
	printf("cos : %f ", cos(deg_to_rad(angle)));
	printf("DISDIFF : %f\n", dis_diff);
	printf("DIS : %f\n", dis);
*/

	int	x_diff = TEXTURE_SIZE;
	if (L_R == 0) //left
		x_diff *= -1;
	// printf("x diff: %i, tan: (%f) y diff: %f\n", x_diff,tan (deg_to_rad(angle)), y_diff);
	// printf("P(XY): %i, %i\n\n", P_x, P_y);
	// printf("B(XY): %i, %i\n", B_x, B_y);

char val;
	while (B_x < WIDTH && B_x > 0 && B_y > 0 && B_y < HEIGHT)
	{
		// mark_pnt(gi, B_x, B_y, 0xFF00FFFF);

		if (U_D == 0)
		{
			if (L_R == 0)
				val = coors_in_map(gi, B_x - 1, B_y - 1);
			else
				val = coors_in_map(gi, B_x + 1, B_y - 1);
		}
		else
		{
			if (L_R == 0)
				val = coors_in_map(gi, B_x - 1, B_y + 1);
			else
				val = coors_in_map(gi, B_x + 1, B_y + 1);
		}
		if ( val == '1')
		{
			return (fabs(dis));
		}

		B_x += x_diff;
		B_y += y_diff;
		dis += dis_diff;
		// printf("B(XY): %i, %i\n", B_x, B_y);
	}
	return (fabs(dis));
}