/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:11:08 by nroth             #+#    #+#             */
/*   Updated: 2023/10/17 17:32:39 by ymorozov         ###   ########.fr       */
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

void	line(mlx_image_t *img, int a[2], int b[2])
{
	float		steps[2];
	int			c[2];
	uint32_t	color = 0x3F51B5FF;
	int			max;

	if (a[0] == b[0] && a[1] == b[1])
	{
		mlx_put_pixel(img, a[0], a[1], color);
		return ;
	}
	steps[0] = b[0] - a[0];
	steps[1] = b[1] - a[1];
	c[0] = a[0];
	c[1] = a[1];
	max = fmax(fabs(steps[0]), fabs(steps[1]));
	if (max == 0)
		return ;
	steps[0] /= max;
	steps[1] /= max;
	while ((int)(b[0] - c[0]) || (int)(b[1] - c[1]))
	{
		mlx_put_pixel(img, c[0], c[1], color);
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
int margin;
	x = -1;
	test = print_bcg(gi);
	if (!test)
		return (NULL);
	ang_incr = 60.0 / 1600.0;

 	while (++x < WIDTH)
	{
		// printf("ANGLE increase: %f\n", angle_increase);
		dis = get_dist(gi, gi->player->orientation + (FOV / 2) - (ang_incr * x));
		printf("dist: %f\n", dis);
		

		// printed_height = round ((32 * 277) / dis);
		printed_height = round ((32 * (WIDTH * 0.5 / tan(dtr(FOV / 2)))) / dis);
		printf("PRINTED HEIGHT: %d\n", printed_height);
		if (printed_height > HEIGHT)
			printed_height = HEIGHT;
		// if (printed_height <= HEIGHT)
		// {
		margin = (HEIGHT - printed_height) / 2;
		line(test, (int[2]){x, margin}, (int[2]){x, margin + printed_height});
		// }

	printf("height: %i\n", printed_height);
	printf("margin: %i\n", margin);
	printf("Axy: %i %i, Bxy:%i, %i \n\n", x, margin, x, margin + printed_height);

	}
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

void mark_pnt(t_gameInfo	*gi, int x, int y, uint32_t color)
{
	if (x < 1 || x > WIDTH - 1 || y < 1 || y > HEIGHT - 1)
		return ;
	mlx_put_pixel(gi->screen_image, x - 1, y - 1, color);
	mlx_put_pixel(gi->screen_image, x - 1, y, color);
	mlx_put_pixel(gi->screen_image, x - 1, y + 1, color);

	mlx_put_pixel(gi->screen_image, x, y - 1, color);
	mlx_put_pixel(gi->screen_image, x, y, color);
	mlx_put_pixel(gi->screen_image, x, y + 1, color);

	mlx_put_pixel(gi->screen_image, x + 1, y - 1, color);
	mlx_put_pixel(gi->screen_image, x + 1, y, color);
	mlx_put_pixel(gi->screen_image, x + 1, y + 1, color);

}


void	print_screen(t_gameInfo *game_info)
{
	mlx_image_t	*img;

	img = create_screen_image(game_info);
	if (!img)
	{
		printf ("ERR printscreen\n");
		return ;
	}
	mlx_delete_image(game_info->mlx, game_info->screen_image);
	game_info->screen_image = img;

/* 	int vert_dis, horiz_dis, dis;
	double angle;

	for(int a = 30; a > -30 ; a -= 3)
	{
		angle = (game_info->player->orientation + a);
		if (angle < 0)
			angle += 360;

		dis = get_dist(game_info)
		if (dis != INT_MAX)
		{
			for(int i = 0; i < dis; i++)
				draw_dot(game_info, angle, i);
		}
	} */

	mlx_image_to_window(game_info->mlx, game_info->screen_image, 0, 0);
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

