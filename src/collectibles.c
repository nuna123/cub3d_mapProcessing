/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:25:33 by nroth             #+#    #+#             */
/*   Updated: 2023/09/25 13:25:34 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	star_horiz_init(t_gameInfo *gi, double a, double pl[2], double dot[2])
{
	pl[0] = gi->player->x + floor(gi->player_size / 2);
	pl[1] = gi->player->y + floor(gi->player_size / 2);
	dot[0] = (((int)(pl[0] / gi->txtr_size))
			+ (a < 90 || a > 270)) * gi->txtr_size;
	dot[1] = pl[1] - ((dot[0] - pl[0]) * tan(dtr(a)));
}
// 0 - 7
// 8 - 23
// 24 - 31

static double	star_get_horiz_dist(t_gameInfo *gi, double a)
{
	double	pl[2];
	double	dot[2];
	double	diff[2];
	double	dis_diff;
	double	dis;

	if (a == 90 || a == 270)
		return (-1);
	star_horiz_init(gi, a, pl, dot);
	dis_diff = fabs(gi->txtr_size / cos(dtr(a)));
	dis = fabs(((pl[0] - dot[0]) / cos(dtr(a))));
	diff[1] = -1 * sin(dtr(a)) * dis_diff;
	diff[0] = gi->txtr_size - (((a > 90 && a < 270)) * gi->txtr_size * 2);
	while (dot[0] < (gi->map_info->map_width * gi->txtr_size) && dot[0] > 0
		&& dot[1] > 0 && dot[1] < (gi->map_info->map_height * gi->txtr_size))
	{
		if (fmod(dot[1], gi->txtr_size) > 7 && fmod(dot[1], gi->txtr_size) < 24)
		{

			if (coors_in_map(gi, dot[0] - (a > 90 && a < 270), dot[1] - (
					(fmod(dot[1], gi->txtr_size) == 0) && (a < 180))) == 'C')
				return (dis);
		}
		dot[0] += diff[0];
		dot[1] += diff[1];
		dis += dis_diff;
	}
	return (-1);
}

static void	star_vert_init(t_gameInfo *gi, double a, double pl[2], double dot[2])
{
	pl[0] = (double) gi->player->x + floor(gi->player_size / 2);
	pl[1] = (double) gi->player->y + floor(gi->player_size / 2);
	dot[1] = (((int)(pl[1] / gi->txtr_size) + (a > 180))) * gi->txtr_size;
	dot[0] = pl[0] + ((a != 90 && a != 270) * ((pl[1] - dot[1]) / tan(dtr(a))));
}

static double	star_get_vert_dist(t_gameInfo *gi, double a)
{
	double	pl[2];
	double	dot[2];
	double	diff[2];
	double	dis_diff;
	double	dis;

	if (a == 0 || a == 180)
		return (-1);
	star_vert_init(gi, a, pl, dot);
	dis_diff = fabs((gi->txtr_size / sin(dtr(a))));
	diff[0] = dis_diff * cos (dtr(a));
	dis = fabs((fabs(pl[1] - dot[1]) / sin(dtr(180 - a))));
	diff[1] = gi->txtr_size - (a < 180) * gi->txtr_size * 2;
	while (dot[0] < (gi->map_info->map_width * gi->txtr_size) && dot[0] > 0
		&& dot[1] > 0 && dot[1] < (gi->map_info->map_height * gi->txtr_size))
	{
		if (fmod(dot[0], gi->txtr_size) > 7 && fmod(dot[0], gi->txtr_size) < 24)
		{
			if (coors_in_map (gi, dot[0] - ((fmod(dot[0], gi->txtr_size) == 0)
						&& (a > 90 && a < 270)), dot[1] - (a < 180)) == 'C')
				return (dis);
		}
		dot[0] += diff[0];
		dot[1] += diff[1];
		dis += dis_diff;
	}
	return (-1);
}

double	star_get_dist(t_gameInfo *gi, double angle)
{
	float			vert_dis;
	float			horiz_dis;
	double			corr_ang;

	if (angle < 360)
		corr_ang = (fmod((angle + 360), 360)
				- (gi->player->angle - gi->offset));
	else
		corr_ang = (angle - (gi->player->angle - gi->offset));

	horiz_dis = (float)star_get_horiz_dist(gi, fmod((angle + 360), 360));
	vert_dis = (float)star_get_vert_dist(gi, fmod((angle + 360), 360));

	if (!(vert_dis == -1 && horiz_dis == -1))
		printf("vert: %f, horiz: %f\n", vert_dis, horiz_dis);

	// define_texture(horiz_dis, vert_dis, angle, txtr);
	if (vert_dis == -1 && horiz_dis == -1)
		return (-1);
	if (vert_dis == -1)
		return (horiz_dis * cos(dtr(corr_ang)));
	if (horiz_dis == -1)
		return (vert_dis * cos(dtr(corr_ang)));
	if (horiz_dis <= vert_dis)
		return (horiz_dis * cos(dtr(corr_ang)));
	return (vert_dis * cos(dtr(corr_ang)));
}

t_star *make_new_star(int x, int y, int size)
{
	t_star *new_star;

	new_star = ft_calloc(sizeof(t_star), 1);
	//ERROR HANDLING

	new_star->x = x;
	new_star->y = y;
	new_star->size = size;

	return new_star;
}

t_star	**get_stars(t_gameInfo *gi)
{
	t_star		**stars = NULL;
	t_star		*new_star = NULL;
	int			x;
	int			temp_x;
	double		dis;
	int			printed_height;
	int			star_c = 0;

	x = -1;
	while (++x < WIDTH)
	{
		dis = star_get_dist(gi,
				gi->player->angle + (FOV / 2)
				- ((FOV / (double) WIDTH) * x) - gi->offset);
		temp_x = x;

		if (x == 0 && dis != -1)
		{
			while (dis != -1.0)
			{
				temp_x--;
				dis = star_get_dist(gi,
					gi->player->angle + (FOV / 2)
					- ((FOV / (double) WIDTH) * temp_x) - gi->offset);
				printf("dis %f\n", dis);
			}

			temp_x++;
			dis = star_get_dist(gi,
					gi->player->angle + (FOV / 2)
					- ((FOV / (double) WIDTH) * temp_x) - gi->offset);
			printf("new dis %f\n", dis);
		}

		if (star_c == 0 && dis != -1)
		{
			printed_height = round(
				(16 * (WIDTH * 0.5 / tan(dtr(FOV / 2)))) / dis);
			star_c = 1;
			new_star = make_new_star(temp_x, (HEIGHT - printed_height) / 2, printed_height);
			stars = (t_star **) ft_arrappend_void((void **)stars, (void *)new_star);
		}
		if (star_c == 1 && dis == -1)
		{
			printf("star end\n");
			star_c = 0;
		}
	}

	return (stars);
}

//vals[0] = x coordinate, vals[1] = y coor, vals[2] = new texture size
//px2print = index of pixel in the texture, [0] = x, [1] = y
// color2print = actual pixel color info
// iters[3] ->	[0] = how many times to print each texture pixle
//				[1] = keep track of how many txtr pixels have been printed
//				[2] = a lil counter


void print_bloc(t_gameInfo *gi, mlx_image_t *img, uint32_t color, uint32_t coors[2], int size)
{
	int x;
	int y;

(void)gi;
	y = -1;
	while (++y < size) //y loop
	{
		x = -1;
		while (++x < size) //x loop
		{
			my_put_pixel(img, x + coors[0], y + coors[1], color);
			// printf("\t(%i, %i)\n", x + coors[0], y + coors[1]);
		}
	}
}

/*
void	star_print(t_gameInfo *gi, t_star *star)
{
	uint32_t	texture_counter[2] = {0,0};
	uint32_t	new_texture_counter[2] = {0,0};
	uint32_t color2print;
	int px2print;

	int	size2print = (int) round(star->size / gi->star_texture->height);

	while (texture_counter[1] < gi->star_texture->height) //y loop
	{
		texture_counter[0] = 0;
		while (texture_counter[0] < gi->star_texture->width) //x loop
		{
			px2print = (texture_counter[0] + (texture_counter[1] * 4)) * 4;
			color2print = get(&(gi->star_texture->pixels[px2print]));

			new_texture_counter[0] = star->x + (texture_counter[0] ) * size2print;
			new_texture_counter[1] = star->y + (texture_counter[1]) * size2print;

			print_bloc (gi, color2print, new_texture_counter, size2print);

			texture_counter[0] ++;
		}
		texture_counter[1] ++;
	}
} */



/* void	print_texture_to_size(t_gameInfo *gi, mlx_image_t *img, int vals[3])
{
	int				px2print[2];
	uint32_t		color2print;
	double			iters[3];

	px2print[0] = 0;
	px2print[1] = 0;

	iters[1] = 0;
	iters[0] = (double)vals[2] / (double)texture->height;
	while (px2print[0] <= ((gi->star_texture->width * gi->star_texture->height) - 1) * 4)
	{
		color2print = get(&(gi->star_texture->pixels[px2print[0]]));
		iters[2] = iters[1] * iters[0];
		while (iters[2] < ((iters[1] + 1) * iters[0]))
			my_put_pixel(img, vals[0], vals[1] + (iters[2]++), color2print);
		px2print[0] += gi->star_texture->width * 4;
		iters[1]++;
	}
} */
void	get_star_img(t_gameInfo *gi)
{
	if (gi->stars)
		ft_arrfree((void **) gi->stars);
	gi->stars = get_stars(gi);

	mlx_delete_image(gi->mlx, gi->stars_image);
	gi->stars_image = mlx_new_image(gi->mlx,
		WIDTH,
		HEIGHT);

	if (!gi->stars)
		printf("NO STARS!\n");
	else if (gi->stars)
	{
		printf("-------------------\n");
		for (int i = 0;gi->stars[i]; i++)
			printf("STAR: x: %i, y: %i, size: %i\n",  gi->stars[i]->x, gi->stars[i]->y,  gi->stars[i]->size);
		for (int i = 0;gi->stars[i]; i++)
		{
			print_bloc(gi, gi->stars_image, PLAYER_COLOR, (uint32_t[2]) {gi->stars[i]->x, gi->stars[i]->y}, gi->stars[i]->size);
			// star_print(gi, gi->stars[i]);
		}
	}
}

