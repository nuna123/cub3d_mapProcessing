#include "game.h"

double get_horiz_dist(t_gameInfo	*gi, double angle)
{

	if (angle == 90 || angle == 270)
		return 0;

	printf("ANGLE: %f\n", angle);
	int U_D = 1;
	if (angle < 180)
		U_D = 0;

	int L_R = 0;
	if (angle < 90 || angle > 270)
		L_R = 1;

	printf("L_R: %i, UD = %i\n", L_R, U_D);

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
			B_y = P_y + (P_x-B_x) * tan(dtr(angle)); // top right
		else
			B_y = P_y - (P_x-B_x) * tan(dtr(360 - angle)); // bottom right
	}

	if (L_R == 0)
	{
		if (U_D == 0)
			B_y = P_y - (P_x-B_x) * tan(dtr(180 - angle)); // top left
		else
			B_y = P_y + (P_x-B_x) * tan(dtr(angle - 180)); // bottom left
	}






	double dis_diff = fabs(TEXTURE_SIZE / cos(dtr(angle)));

	//first value is the hypoteneuse of player to the nearest check point
	double	dis = abs( (int) ((P_x - B_x) / cos(dtr(angle))));


	//how much to add to the y pos in each loop
	double y_diff = -1 * sin(dtr(angle)) * dis_diff;


	printf("dis diff: %f\n", dis_diff);
	printf("y diff: %f\n", y_diff);








			// printf("DIS diff: %f\n", dis_diff);
		//first value is the hypoteneuse of player to the nearest check point




/* 	printf("fabs : %d ", abs(P_y - B_y));
	printf("cos : %f ", cos(dtr(angle)));
	printf("DISDIFF : %f\n", dis_diff);
	printf("DIS : %f\n", dis);
*/

	int	x_diff = TEXTURE_SIZE;
	if (L_R == 0) //left
		x_diff *= -1;
	// printf("x diff: %i, tan: (%f) y diff: %f\n", x_diff,tan (dtr(angle)), y_diff);
	// printf("P(XY): %i, %i\n\n", P_x, P_y);
	// printf("B(XY): %i, %i\n", B_x, B_y);



	// int check_x, check_y;
	char val;
	while (B_x < WIDTH && B_x > 0 && B_y > 0 && B_y < HEIGHT)
	{
		printf("\n\n");


		// mark_pnt(gi, B_x, B_y, 0xFF00FFFF);
/* 		check_x = B_x;
		check_y = B_y; */
/*
		if (U_D == 0)
			check_y = floor(check_y / TEXTURE_SIZE) * TEXTURE_SIZE;
		else
			check_y = ceil(check_y / TEXTURE_SIZE) * TEXTURE_SIZE;
		if (L_R == 0)
			check_x = floor(check_x / TEXTURE_SIZE) * TEXTURE_SIZE;
		else
			check_x = ceil(check_x / TEXTURE_SIZE) * TEXTURE_SIZE; */
printf("B(XY): %i, %i\n", B_x, B_y);
// printf("CHECK(XY): %i, %i\n", check_x, check_y);
		if (U_D == 0)
		{
			if (L_R == 0)
				val = coors_in_map(gi, B_x - (TEXTURE_SIZE / 2), B_y/*  - (TEXTURE_SIZE / 2) */);
			else
				val = coors_in_map(gi, B_x/*  + (TEXTURE_SIZE / 2) */, B_y/*  - (TEXTURE_SIZE / 2) */);
		}
		else
		{
			if (L_R == 0)
				val = coors_in_map(gi, B_x - (TEXTURE_SIZE / 2), B_y + (TEXTURE_SIZE / 2));
			else
				val = coors_in_map(gi, B_x/*  + (TEXTURE_SIZE / 2) */, B_y + (TEXTURE_SIZE / 2));
		}

/* 			if (L_R == 0)
				val = coors_in_map(gi, B_x - TEXTURE_SIZE / 2, B_y);
			else
				val = coors_in_map(gi, B_x + TEXTURE_SIZE / 2, B_y); */

		if (val != '0')
			return (dis);
/* 		if ( val != '0')
		{
			return (fabs(dis));
		} */

		B_x += x_diff;
		B_y += y_diff;
		dis += dis_diff;
	}
	return (fabs(dis));
}