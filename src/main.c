/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:11:08 by nroth             #+#    #+#             */
/*   Updated: 2023/10/26 15:51:14 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// #define PI 3.141592

// DEGREES TO RADIANS
double dtr(double deg)
{
	return(deg * (M_PI / 180));
}

///TODO
	// deg to radians ?
	// One pixel difference in vertia/horizontal check, Top sector
	// Player movements still depend on 8 dirctions while orientation is by 36 (ish?) directions
	// line uses colors - not the given textures for NSWE

uint32_t	get(uint8_t *texture_pixels)
{
	uint32_t	res;

	res = 0;
	res += texture_pixels[0] << 24;
	res += texture_pixels[1] << 16;
	res += texture_pixels[2] << 8;
	res += texture_pixels[3];
	return (res);
}

void	print_texture(mlx_image_t *img, mlx_texture_t *texture,
		int coor_x, int coor_y)
{
	uint32_t	pixel;
	uint32_t	x;
	uint32_t	y;

	y = -1;
	while (++y < texture->height - 1)
	{
		x = -1;
		while (++x < texture->width - 1)
		{
			pixel = (y * texture->height + x) * 4;
			mlx_put_pixel(img, (coor_x + x), (coor_y + y),
				get(&texture->pixels[pixel]));
		}
	}
}


// void	line(mlx_image_t *img, double a[2], double b[2], int txtr)
void	line(mlx_image_t *img, double a[2], double b[2], uint32_t txtr)
{
	double		steps[2];
	double			c[2];
	uint32_t	color;
	double			max;

	color = txtr;
	if (txtr == 0)
		color = 0xFFD54FFF;	//yellow east
	else if (txtr == 1)
		color = 0x4A148CFF;	//purple north
	else if (txtr == 2)
		color = 0xFF6E40FF;	// coral west
	else if (txtr == 3)
		color = 0x388E3CFF;	//green south
	if (a[0] == b[0] && a[1] == b[1])
	{
		mlx_put_pixel(img, (int)a[0], (int)a[1], color);
		return ;
	}
	steps[0] = b[0] - a[0];
	steps[1] = b[1] - a[1];
	c[0] = (float)a[0];
	c[1] = (float)a[1];
	max = fmax(fabs(steps[0]), fabs(steps[1]));
	if (max == 0)
		return ;
	steps[0] /= max;
	steps[1] /= max;
	while (((b[0] - round(c[0])) || (b[1] - round(c[1]))))
	{
		mlx_put_pixel(img, (int)round(c[0]), (int)round(c[1]), color);
		c[0] += steps[0];
		c[1] += steps[1];
	}
}

mlx_image_t	*print_bcg(t_gameInfo	*gi)
{
	mlx_image_t	*test;
	int			x;
	int			y;

	test = mlx_new_image(gi->mlx, WIDTH, HEIGHT);
	if (!test)
		return (NULL);
	y = -1;
	while (++y < HEIGHT / 2 + 1)
	{
		x = -1;
		while (++x < WIDTH)
			mlx_put_pixel(test, x, y, gi->map_info->ceiling_color);
	}
	y--;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			mlx_put_pixel(test, x, y, gi->map_info->floor_color);
	}
	return (test);
}

mlx_image_t	*create_screen_image(t_gameInfo	*gi)
{
	mlx_image_t	*test;
	int			x;
	double			dis;
	double		ang_incr;
	int		printed_height;
	int		margin;
	int	texture = -1; //0 east(yellow), 1 north(purple), 2 west(coral), 3 south(green)
	x = -1;
	test = print_bcg(gi);
	if (!test)
		return (NULL);

	ang_incr = 60.0 / 1600.0;
	// double counter = round(x + 1 / 27);
		// FILE * fp = fopen("log.log", "w+");
		FILE * fp = fopen("/dev/null", "w+");
 	while (++x < WIDTH)
	{
		fprintf(fp, "(player orientation = %d\n", gi->player->orientation);
		dis = get_dist(gi, gi->player->orientation + (FOV / 2) - (ang_incr * x), &texture, &fp);
		// dis = get_dist(gi, gi->player->orientation + (FOV / 2) - (ang_incr * x), &texture);
		// printf("\nDIST: %f\n", dis);
		printed_height = round((32 * (WIDTH * 0.5 / tan(dtr(FOV / 2)))) / dis);
		// printf("PRINTED HEIGHT: %d\n", printed_height);
		if (printed_height > HEIGHT)
			printed_height = HEIGHT;
		// if (printed_height <= HEIGHT)
		// {
		// fprintf(fp, "(32 * (WIDTH * 0.5 / tan(dtr(FOV / 2)))) / dis =  %f,\n", (32 * (WIDTH * 0.5 / tan(dtr(FOV / 2)))) / dis);
		margin = (HEIGHT - printed_height) / 2;
			fprintf(fp, "dis =  %f, printed_height = %i, margin = %d\n", dis, printed_height, margin);
			fprintf(fp, "	dot1(x: %i y = %i), dot2(x = %d, y = %d). COLOUR = %d\n", x, margin, x, margin + printed_height, texture);
			fprintf(fp, "--------------------------------------------------------------------------------------------------------\n");
		line(test, (double[2]){x, margin}, (double[2]){x, margin + printed_height}, texture);
		// }

	// printf("height: %i\n", printed_height);
	// printf("margin: %i\n", margin);
	// printf("Axy: %i %i, Bxy:%i, %i \n\n", x, margin, x, margin + printed_height);
	}
	// line(test, (double[2]){971, 0}, (double[2]){971, HEIGHT}, -1);
	return (test);
}
/* mlx_image_t	*create_screen_image(t_gameInfo	*gi)
{
	mlx_image_t	*test;
	int			x;
	int			y;

	y = -1;
	test = print_bcg(gi);
	if (!test)
		return (NULL);
	while (gi->map_info->map[++y])
	{
		x = -1;
		while (gi->map_info->map[y][++x])
		{
			if (gi->map_info->map[y][x] == '1')
				print_texture(test, gi->wall_texture,
					TEXTURE_SIZE * x, TEXTURE_SIZE * y );
			else if (gi->map_info->map[y][x] == '0')
				print_texture(test, gi->bckg_texture,
					TEXTURE_SIZE * x, TEXTURE_SIZE * y);
		}
	}
	print_texture(test, gi->player_texture, gi->player->x, gi->player->y);
	return (test);
} */

void draw_dot(t_gameInfo	*gi, double angle, int dis)
{
	double dot_x;
	double dot_y;

/* 	dot_x = (gi->player->x) + (dis * cos(dtr(angle)));
	dot_y = (gi->player->y) - (dis * sin(dtr(angle))); */

	dot_x = (gi->player->x + floor(PLAYER_SIZE / 2)) + (dis * cos(dtr(angle)));
	dot_y = (gi->player->y + floor(PLAYER_SIZE / 2)) - (dis * sin(dtr(angle)));
	if (dot_x < 1 || dot_x > WIDTH - 1 || dot_y < 1 || dot_y > HEIGHT - 1)
		return ;
	mlx_put_pixel(gi->screen_image, (int) dot_x, (int) dot_y, 0x0000FFFF);

}

void mark_pnt(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (x < 1 || x > WIDTH - 1 || y < 1 || y > HEIGHT - 1)
		return ;
	mlx_put_pixel(img, x - 1, y - 1, color);
	mlx_put_pixel(img, x - 1, y, color);
	mlx_put_pixel(img, x - 1, y + 1, color);

	mlx_put_pixel(img, x, y - 1, color);
	mlx_put_pixel(img, x, y, color);
	mlx_put_pixel(img, x, y + 1, color);

	mlx_put_pixel(img, x + 1, y - 1, color);
	mlx_put_pixel(img, x + 1, y, color);
	mlx_put_pixel(img, x + 1, y + 1, color);

}


void	print_screen(t_gameInfo *gi)
{
	mlx_image_t	*img;

	img = create_screen_image(gi);
	if (!img)
	{
		printf ("ERR printscreen\n");
		return ;
	}
	mlx_delete_image(gi->mlx, gi->screen_image);
	gi->screen_image = img;

/* 	int vert_dis, horiz_dis, dis;
	double angle;

	for(int a = 30; a > -30 ; a -= 3)
	{
		angle = (gi->player->orientation + a);
		if (angle < 0)
			angle += 360;

		dis = get_dist(gi)
		if (dis != INT_MAX)
		{
			for(int i = 0; i < dis; i++)
				draw_dot(gi, angle, i);
		}
	} */
	draw_minimap (gi, gi->screen_image, (int[2]){20, 20});
	mlx_image_to_window(gi->mlx, gi->screen_image, 0, 0);
}

int	main(int argc, char *argv[])
{
	 t_gameInfo	*game_info;

	if (argc <= 1)
		return (printf ("Error!\nNo map path specified.\n"), 1);
	game_info = init_game_info(argv);
	if (!game_info)
		exit(-1);
	print_screen(game_info);
	mlx_close_hook(game_info->mlx, closeme, game_info);
	mlx_key_hook(game_info->mlx, key_hooker, game_info);
	mlx_loop(game_info->mlx);
	mlx_terminate(game_info->mlx);
/*
	printf ("%c\n\n", coors_in_map(game_info, 0, 0));
	printf ("%c\n\n", coors_in_map(game_info, TEXTURE_SIZE, 0));
	printf ("%c\n\n", coors_in_map(game_info, TEXTURE_SIZE + 1, 0)); */
	return (EXIT_SUCCESS);
}

