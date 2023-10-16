double get_horz_dist(t_gameInfo	*gi, double angle)
{

	if (angle == 90 || angle == 270)
		return 0;

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
	//how much to add to the y pos in each loop
	double y_diff = TEXTURE_SIZE * tan (dtr(angle));
	if (angle == 45 || angle == 315)
		y_diff *= -1;


	//first value is the hypoteneuse of player to the nearest check point
	double dis_diff = TEXTURE_SIZE / cos(dtr(angle));
			printf("DIS diff: %f\n", dis_diff);
		//first value is the hypoteneuse of player to the nearest check point

	double	dis;
	if (U_D == 0 && L_R == 0)
		dis = (TEXTURE_SIZE - (P_x % TEXTURE_SIZE)) / cos(dtr(180 - angle));
	if (U_D == 1 && L_R == 0)
		dis = (TEXTURE_SIZE - (P_x % TEXTURE_SIZE)) / cos(dtr(angle - 180));
	if (U_D == 0 && L_R == 1)
		dis = (TEXTURE_SIZE - (P_x % TEXTURE_SIZE)) / cos(dtr(angle));
	if (U_D == 1 && L_R == 1)
		dis = (TEXTURE_SIZE - (P_x % TEXTURE_SIZE)) / cos(dtr(360 - angle));

	if(angle == 225 || angle == 135)
		dis += dis_diff;


	int	x_diff = TEXTURE_SIZE;
	if (L_R == 0) //left
		x_diff *= -1;
	printf("x diff: %i, tan: (%f) y diff: %f\n", x_diff,tan (dtr(angle)), y_diff);
	printf("P(XY): %i, %i\n\n", P_x, P_y);
	printf("B(XY): %i, %i\n", B_x, B_y);


	while (B_x < WIDTH && B_x > 0 && B_y > 0 && B_y < HEIGHT)
	{


		mark_pnt(gi, B_x, B_y, 0xFF00FFFF);

		if (coors_in_map(gi, B_x, B_y) == '1')
			return (fabs(dis));
		B_x += x_diff;
		B_y += y_diff;
		dis += dis_diff;
		// printf("B(XY): %i, %i\n", B_x, B_y);
	}
	return (fabs(dis));
}