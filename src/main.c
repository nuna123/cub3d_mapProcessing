/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:11:08 by nroth             #+#    #+#             */
/*   Updated: 2023/10/05 17:31:05 by ymorozov         ###   ########.fr       */
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
}

void draw_dot(t_gameInfo	*gi, double angle, int dis)
{
	double dot_x;
	double dot_y;

/* 	dot_x = (gi->player->x) + (dis * cos(dtr(angle)));
	dot_y = (gi->player->y) - (dis * sin(dtr(angle))); */
	dot_x = (gi->player->x + PLAYER_SIZE/2) + (dis * cos(dtr(angle)));
	dot_y = (gi->player->y + PLAYER_SIZE/2) - (dis * sin(dtr(angle)));
	if (dot_x < 1 || dot_x > WIDTH - 1 || dot_y < 1 || dot_y > HEIGHT - 1)
		return ;
	mlx_put_pixel(gi->screen_image, (int) dot_x, (int) dot_y, 0xFF0000FF);

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
	printf("\n--------------------------------------------------------\n");
	printf("\n--------------------------------------------------------\n");
	mlx_image_t	*img;

	img = create_screen_image(game_info);
	if (!img)
	{
		printf("ERR printscreen\n");
		return ;
	}
	mlx_delete_image(game_info->mlx, game_info->screen_image);
	game_info->screen_image = img;
/*
	double vert_dis = get_vert_dist(game_info,(double)game_info->player->orientation);

	double horiz_dis = get_horiz_dist(game_info,(double)game_info->player->orientation);

	double dis = vert_dis;
	if (!vert_dis)
		dis = horiz_dis;
	else if (!horiz_dis)
		dis = vert_dis;
	else if (horiz_dis < vert_dis)
		dis = horiz_dis;
	else if (vert_dis < horiz_dis)
		dis = vert_dis;

	for(int i = 0; i < (int) dis; i++)
	{
		draw_dot(game_info,(double)game_info->player->orientation, i);
	} */

	int vert_dis, horiz_dis, dis;
	double angle;
	// double arr[] = {0, 45, 90 , 135,  180, 225, 270, 315};

	for(int a = 30; a > -30 ; a -= 10)
	{
	// int a = +30;
		angle = (game_info->player->orientation + a);
		if (angle < 0)
			angle += 360;

		printf("\n--------------\na: %i, angle %f\n",a ,  angle);


		vert_dis = get_vert_dist(game_info,angle);
		horiz_dis = get_horiz_dist(game_info,angle);
		// vert_dis = INT_MAX;

		dis = vert_dis;
		if (horiz_dis < vert_dis)
			dis = horiz_dis;


		// printf("dis: %f\n", dis);
		if (dis != INT_MAX)
{		for(int i = 0; i < dis; i++)
		{
			draw_dot(game_info, angle, i);
		}}
	}

	mlx_image_to_window(game_info->mlx, game_info->screen_image, 0, 0);
}

int	main(int argc, char *argv[])
{
	t_gameInfo	*game_info;

	if (argc <= 1)
		return (printf("Error!\nNo map path specified.\n"), 1);
	game_info = init_game_info(argv);
	if (!game_info)
		exit(-1);
	print_screen(game_info);
	mlx_close_hook(game_info->mlx, closeme, game_info);
	mlx_key_hook(game_info->mlx, key_hooker, game_info);
	mlx_loop(game_info->mlx);
	mlx_terminate(game_info->mlx);
	return (EXIT_SUCCESS);
}

