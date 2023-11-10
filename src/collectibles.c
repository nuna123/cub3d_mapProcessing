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
char	star_coors_in_map(t_gameInfo *gi, int x, int y, int *id)
{
	if (x < 0 || y < 0)
		return (printf("1ERR! %i, %i\n", x, y), -1);
	if (y / gi->txtr_size >= gi->map_info->map_height
		|| x / gi->txtr_size >= gi->map_info->map_width)
		return (printf("2ERR! %i, %i\n\n", x, y), -1);

/* 	printf("\tBLOCK CHECKED  %i, %i (%i)\n",
		(x / gi->txtr_size),
		(y / gi->txtr_size),
		((y / gi->txtr_size) * gi->map_info->map_width)  + (x / gi->txtr_size)); */

	*id = ((y / gi->txtr_size) * gi->map_info->map_width)  + (x / gi->txtr_size);

	return (gi->map_info->map
		[(y / gi->txtr_size)]
		[(x / gi->txtr_size)]);
}
static void	star_horiz_init(t_gameInfo *gi, double a, double pl[2], double dot[2])
{
	pl[0] = gi->player->x + floor(gi->player_size / 2);
	pl[1] = gi->player->y + floor(gi->player_size / 2);
	dot[0] = (((int)(pl[0] / gi->txtr_size))
			+ (a < 90 || a > 270)) * gi->txtr_size;
	dot[0] += 8;
	dot[1] = pl[1] - ((dot[0] - pl[0]) * tan(dtr(a)));
}

static double	star_get_horiz_dist(t_gameInfo *gi, double a, int *hor_block)
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
		if (coors_in_map(gi, dot[0] - (a > 90 && a < 270), dot[1] - (
				(fmod(dot[1], gi->txtr_size) == 0) && (a < 180))) == 'C')
		{
			star_coors_in_map(gi, dot[0] - (a > 90 && a < 270), dot[1] - (
				(fmod(dot[1], gi->txtr_size) == 0) && (a < 180)), hor_block);
			/* *hor_block = (dot[0]) / gi->txtr_size;
			*hor_block += gi->map_info->map_width * (dot[1]/ gi->txtr_size); */
			/* *hor_block = (dot[0] - (a > 90 && a < 270)) / gi->txtr_size;
			*hor_block += gi->map_info->map_width * ((dot[1] - ((fmod(dot[1], gi->txtr_size) == 0) && (a < 180)))/ gi->txtr_size);
			 */
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
	dot[1] += 8;
	dot[0] = pl[0] + ((a != 90 && a != 270) * ((pl[1] - dot[1]) / tan(dtr(a))));
}

static double	star_get_vert_dist(t_gameInfo *gi, double a, int *ver_block)
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

		if (coors_in_map (gi, dot[0] - ((fmod(dot[0], gi->txtr_size) == 0)
						&& (a > 90 && a < 270)), dot[1] - (a < 180)) == 'C')
		{
			star_coors_in_map (gi, dot[0] - ((fmod(dot[0], gi->txtr_size) == 0)
						&& (a > 90 && a < 270)), dot[1] - (a < 180), ver_block);
	/* 		if (round(fmod(dot[0], gi->txtr_size)) == 0.0)
				return (printf("ooooooooooooooooooooooooooooooooooooo"), -1); */
			/* *ver_block = (dot[0]) / gi->txtr_size;
			*ver_block += gi->map_info->map_width * ((dot[1]) / gi->txtr_size);
			*ver_block = (dot[0] - ((fmod(dot[0], gi->txtr_size) == 0) && (a > 90 && a < 270))) / gi->txtr_size;
			*ver_block += gi->map_info->map_width * ((dot[1] - (a < 180)) / gi->txtr_size); */

			return (dis);
		}
		dot[0] += diff[0];
		dot[1] += diff[1];
		dis += dis_diff;
	}
	return (-1);
}

double	star_get_dist(t_gameInfo *gi, double angle, int *block)
{
	float			vert_dis;
	float			horiz_dis;
	double			corr_ang;

	int ver_block;
	int horiz_block;

	if (angle < 360)
		corr_ang = (fmod((angle + 360), 360)
				- (gi->player->angle - gi->offset));
	else
		corr_ang = (angle - (gi->player->angle - gi->offset));

	horiz_dis = (float)star_get_horiz_dist(gi, fmod((angle + 360), 360), &horiz_block);
	vert_dis = (float)star_get_vert_dist(gi, fmod((angle + 360), 360), &ver_block);
/*
	if (!(vert_dis == -1 && horiz_dis == -1))
		printf("vert: %f, horiz: %f\n", vert_dis, horiz_dis); */

	if (vert_dis == -1 && horiz_dis == -1)
		return (-1);
	if (vert_dis == -1)
		return ( (*block = horiz_block), horiz_dis * cos(dtr(corr_ang)));
	if (horiz_dis == -1)
		return ( (*block = ver_block), vert_dis * cos(dtr(corr_ang)));
	if (horiz_dis <= vert_dis)
		return ((*block = horiz_block), horiz_dis * cos(dtr(corr_ang)));
	return ((*block = ver_block), vert_dis * cos(dtr(corr_ang)));
}

t_star *make_new_star(int x, int y, int width, int height)
{
	t_star *new_star;

	new_star = ft_calloc(sizeof(t_star), 1);
	//ERROR HANDLING

	new_star->x = x;
	new_star->y = y;
	new_star->width = width;
	new_star->height = height;

	return new_star;
}
void	get_star(t_gameInfo *gi, int x, t_star	***stars)
{
	int star_start;
	int star_end;
	int old_block;
	int block;
	double dis;
	double min_dis = WIDTH;
	t_star	*new_star;


	block = -1;
	old_block = -1;

	dis = WIDTH;
	star_start = x;
	while (dis != -1)
	{
		if (dis < min_dis)
			min_dis = dis;
		dis = star_get_dist(gi,
				gi->player->angle + (FOV / 2)
				- ((FOV / (double) WIDTH) * star_start) - gi->offset, &block);
		if (block != old_block && old_block != -1)
		{
			// printf("Bold block - %i; block - %i -- %i%s\n", old_block, block, star_end, WHITE);
			break;
		}
		star_start--;
		old_block = block;
	}
	star_start ++;

	dis = WIDTH;
	star_end = x;

	old_block = -1;
	block = -1;
	while (dis != -1)
	{
		if (dis < min_dis)
			min_dis = dis;
		dis = star_get_dist(gi,
				gi->player->angle + (FOV / 2)
				- ((FOV / (double) WIDTH) * star_end) - gi->offset, &block);
		if (block != old_block && old_block != -1)
		{
			// printf("Bold block - %i; block - %i -- %i%s\n", old_block, block, star_end, WHITE);
			get_star(gi,star_end , stars);
			break;
		}

		old_block = block;
		star_end++;
	}
	star_end--;

	star_start += ((star_end - star_start) - ((star_end - star_start) / 2)) / 2;
	min_dis = round(
				(32 * (WIDTH * 0.5 / tan(dtr(FOV / 2)))) / min_dis);
	new_star = make_new_star(star_start, ((HEIGHT - min_dis) / 2) + 50, ((star_end - star_start) / 2), min_dis / 2);

	if (new_star->x > WIDTH || new_star->x + new_star->width <= 0)
		free(new_star);
	else if (new_star->y > HEIGHT || new_star->y + new_star->height <= 0 || new_star->width < 10)
		free(new_star);
	else
		*stars = (t_star **) ft_arrappend_void((void **) (*stars), (void *)new_star);
}

t_star	**get_stars(t_gameInfo *gi)
{
	t_star		**stars = NULL;
	int			x;
	double		dis;
	double			star_c = 0;
	int unused;

	x = -1;
	while (++x < WIDTH)
	{
		dis = star_get_dist(gi,
				gi->player->angle + (FOV / 2)
				- ((FOV / (double) WIDTH) * x) - gi->offset, &unused);

		if ((star_c == -1 || star_c == 0) && dis != -1)
		{
			// printf("star start\n");
			get_star(gi, x, &stars);
			// stars = (t_star **) ft_arrappend_void((void **)stars, (void *)new_star);
		}
		if (star_c != -1 && dis == -1)
		{
			// printf("star end\n");
			star_c = 0;
		}
		star_c = dis;
	}

	return (stars);
}

//vals[0] = x coordinate, vals[1] = y coor, vals[2] = new texture size
//px2print = index of pixel in the texture, [0] = x, [1] = y
// color2print = actual pixel color info
// iters[3] ->	[0] = how many times to print each texture pixle
//				[1] = keep track of how many txtr pixels have been printed
//				[2] = a lil counter


void print_bloc(t_gameInfo *gi, mlx_image_t *img, uint32_t color, uint32_t coors[2], int w, int h)
{
	int x;
	int y;

(void)gi;
	y = -1;
	while (++y < h) //y loop
	{
		x = -1;
		while (++x < w) //x loop
		{
			my_put_pixel(img, x + coors[0], y + coors[1], color);
			// printf("\t(%i, %i)\n", x + coors[0], y + coors[1]);
		}
	}
}


void	star_print(t_gameInfo *gi, t_star *star)
{
	uint32_t	texture_counter[2] = {0,0};
	uint32_t	new_texture_counter[2] = {0,0};
	uint32_t color2print;
	int px2print;

	int	size2print_h = (int) round(star->height / gi->star_texture->height);
	int	size2print_w = (int) round(star->width / gi->star_texture->width);

	while (texture_counter[1] < gi->star_texture->height) //y loop
	{
		texture_counter[0] = 0;
		while (texture_counter[0] < gi->star_texture->width) //x loop
		{
			px2print = (texture_counter[0] + (texture_counter[1] * 4)) * 4;
			color2print = get(&(gi->star_texture->pixels[px2print]));

			new_texture_counter[0] = star->x + (texture_counter[0] ) * size2print_w;
			new_texture_counter[1] = star->y + (texture_counter[1]) * size2print_h;

			print_bloc (gi, gi->stars_image, color2print, new_texture_counter, size2print_w, size2print_h);

			texture_counter[0] ++;
		}
		texture_counter[1] ++;
	}
}



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
			printf("STAR: x: %i, y: %i, width: %i, height: %i\n",  gi->stars[i]->x, gi->stars[i]->y,  gi->stars[i]->width, gi->stars[i]->height);
		for (int i = 0;gi->stars[i]; i++)
		{
			print_bloc(gi, gi->stars_image, PLAYER_COLOR, (uint32_t[2]) {gi->stars[i]->x, gi->stars[i]->y}, gi->stars[i]->width, gi->stars[i]->height);
			// star_print(gi, gi->stars[i]);
		}
	}
}

