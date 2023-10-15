#include "game.h"

double get_vert_dist(t_gameInfo	*gi, double angle)
{
	if (angle == 0 || angle == 180)
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


		B_y = (P_y / TEXTURE_SIZE) * TEXTURE_SIZE;

		if (U_D == 0) // UP
			B_y = ((int)(P_y / TEXTURE_SIZE)) * TEXTURE_SIZE;
		else // DOWN
			B_y = ((int)(P_y / TEXTURE_SIZE + 1)) * TEXTURE_SIZE;


		if (U_D == 0) // UP
			B_x = P_x + (abs(P_y - B_y) / tan(deg_to_rad(angle)));
		else
			B_x = P_x - (abs(P_y - B_y) / tan(deg_to_rad(angle)));
		if (angle == 90 || angle == 270)
			B_x = P_x;

		// printf("B(XY): %i, %i\n", B_x, B_y);




	double dis_diff =  fabs(TEXTURE_SIZE / sin(deg_to_rad(angle)));
	// printf("DIS diff: %f\n\n", dis_diff);
	// printf("angle : %f, sin %f \n", angle, sin (deg_to_rad(angle)));


	//how much to add to the x pos in each loop
	double x_diff = dis_diff * cos (deg_to_rad(angle));

	double	dis = fabs(abs(P_y - B_y) / sin(deg_to_rad(180 - angle)));


	int	y_diff = TEXTURE_SIZE;
	if (U_D == 0) //up
		y_diff *= -1;

	// printf("x diff: %f, sin: (%f) y diff: %i\n", x_diff,sin (deg_to_rad(angle)), y_diff);

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

		if (val == '1')
			return (fabs(dis));
		B_x += x_diff;
		B_y += y_diff;
		dis += dis_diff;
	}
	return (fabs(dis));
}
