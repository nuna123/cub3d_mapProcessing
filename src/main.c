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
#include <math.h>

// #define PI 3.141592

double deg_to_rad(double deg)
{
	return(deg * (M_PI / 180));
}

///TODO
	// regulate map to width - pad with 1s
	// deg to radians ?

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
	while (++y < texture->height)
	{
		x = -1;
		while (++x < texture->width)
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
					TEXTURE_SIZE * x, TEXTURE_SIZE * y);
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

	dot_x = (gi->player->x) + (dis * cos(deg_to_rad(angle)));
	dot_y = (gi->player->y) - (dis * sin(deg_to_rad(angle)));
/* 	dot_x = (gi->player->x + PLAYER_SIZE/2) + (dis * cos(deg_to_rad(angle)));
	dot_y = (gi->player->y + PLAYER_SIZE/2) - (dis * sin(deg_to_rad(angle))); */

	mlx_put_pixel(gi->screen_image, (int) dot_x, (int) dot_y, 0xFF0000FF);

}

double get_dist(t_gameInfo	*gi, double angle)
{
	double dis = 0;
	//this is checking from top left corner, not center of player
	double y_pos = (gi->player->y / TEXTURE_SIZE);
	double ray_x = (gi->player->x / TEXTURE_SIZE + 1) * TEXTURE_SIZE;
	double ray_y = y_pos * TEXTURE_SIZE;

	while (ray_x < WIDTH)
	{
		dis += TEXTURE_SIZE / cos(deg_to_rad(angle));
		printf("dray_x=%f; distance:%f, %f\n", ray_x, dis,TEXTURE_SIZE / cos(deg_to_rad(angle) ));


		//check position
		if (coors_in_map(gi, ray_x, ray_y) == '1')
			return (dis);
		y_pos -= tan(deg_to_rad(angle)) * TEXTURE_SIZE;
		printf("y ps:%f, %f\n", y_pos, tan(deg_to_rad(angle)) * TEXTURE_SIZE);

		// ray_y = y_pos / TEXTURE_SIZE;
		ray_x += TEXTURE_SIZE;
	}

	return (dis);
}

void	print_screen(t_gameInfo *game_info)
{
	mlx_image_t	*img;

	img = create_screen_image(game_info);
	if (!img)
	{
		printf("ERR printscreen\n");
		return ;
	}
	mlx_delete_image(game_info->mlx, game_info->screen_image);
	game_info->screen_image = img;


	if (game_info->player->orientation != 90 && game_info->player->orientation != 270)
	{
		double dis = get_dist(game_info, (double) game_info->player->orientation);
		printf("DIS: %f\n", dis);

/* 		for(int a = -30; a < 30; a++)
		{ */
			for(int i = 0; i < (int) dis; i++)
				{
					// printf("i: %i\n", )
					draw_dot(game_info,(double) game_info->player->orientation, i);
				}
		// }
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
