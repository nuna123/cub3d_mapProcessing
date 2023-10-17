#include "game.h"

double get_horiz_dist(t_gameInfo	*gi, double angle)
{

	if (angle == 90 || angle == 270)
		return INT_MAX;

	dprintf(FD, "ANGLE: %f\n", angle);
	int U_D = 1;
	if (angle < 180)
		U_D = 0;

	int L_R = 0;
	if (angle < 90 || angle > 270)
		L_R = 1;

	// dprintf(FD, "L_R: %f, UD = %f\n", L_R, U_D);

	//PLAYER XY
	double P_x = gi->player->x + floor(PLAYER_SIZE / 2);
	double P_y = gi->player->y + floor(PLAYER_SIZE / 2);
printf("\nPLAYER XY = %f, %f\n", P_x, P_y);
	//FIRST INTERSECTION XY
	double B_x;
	double B_y;


	B_x = (((int) (P_x / TEXTURE_SIZE)) + L_R) * TEXTURE_SIZE;




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


	dprintf(FD, "dis diff: %f\n", dis_diff);
	dprintf(FD, "y diff: %f\n", y_diff);

			// dprintf(FD, "DIS diff: %f\n", dis_diff);
		//first value is the hypoteneuse of player to the nearest check point

/* 	dprintf(FD, "fabs : %d ", abs(P_y - B_y));
	dprintf(FD, "cos : %f ", cos(dtr(angle)));
	dprintf(FD, "DISDIFF : %f\n", dis_diff);
	dprintf(FD, "DIS : %f\n", dis);
*/

	int	x_diff = TEXTURE_SIZE;
	if (L_R == 0) //left
		x_diff *= -1;
	// dprintf(FD, "x diff: %f, tan: (%f) y diff: %f\n", x_diff,tan (dtr(angle)), y_diff);
	// dprintf(FD, "P(XY): %f, %f\n\n", P_x, P_y);
	// dprintf(FD, "B(XY): %f, %f\n", B_x, B_y);



	while (B_x < WIDTH && B_x > 0 && B_y > 0 && B_y < HEIGHT)
	{


		// mark_pnt(gi, B_x, B_y, 0xFF00FFFF);

		dprintf(FD, "\n\n%sB(XY): %f, %f%s\n",MAG, B_x, B_y, WHT);


		if (coors_in_map(gi,	B_x - (((int) round(B_x) % TEXTURE_SIZE == 0) && (angle > 90 && angle < 270)),
								B_y - (((int) round (B_y) % TEXTURE_SIZE == 0) && (angle < 180)))				 != '0')
			{
				printf("%sfinal xy: %f, %f\n%s",MAG, B_x, B_y, WHT);
				// mark_pnt(gi, B_x, B_y, 0xFF00FFFF);
				return (round(dis));
			}


		B_x += x_diff;
		B_y += y_diff;
		dis += dis_diff;
	}
	return (round((dis)));
}