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


///TODO
	// deg to radians ?
	// One pixel difference in vertia/horizontal check, Top sector
	// line uses colors - not the given textures for NSWE
	//*********
	// void mlx_set_icon(mlx_t* mlx, mlx_texture_t* image);



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
		my_put_pixel(img, (int)a[0], (int)a[1], color);
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
		my_put_pixel(img, (int)round(c[0]), (int)round(c[1]), color);
		c[0] += steps[0];
		c[1] += steps[1];
	}
}

mlx_image_t	*print_bcg(t_gameInfo	*gi)
{
	mlx_image_t	*test;
	int			x;
	int			y;

	test = mlx_new_image(gi->mlx, gi->screen_w, gi->screen_h);
	if (!test)
		return (NULL);
	y = -1;
	while (++y < gi->screen_h / 2 + 1)
	{
		x = -1;
		while (++x < gi->screen_w)
			my_put_pixel(test, x, y, gi->map_info->ceiling_color);
	}
	y--;
	while (++y < gi->screen_h)
	{
		x = -1;
		while (++x < gi->screen_w)
			my_put_pixel(test, x, y, gi->map_info->floor_color);
	}
	return (test);
}

void print_texture(t_gameInfo	*gi,mlx_image_t	*img, int x, int margin, int line_height, int t_idx)
{
// FILE * fp = fopen("log.log", "w+");

	static int texture_offset;
	static int prev_texture = -1;
	mlx_texture_t *texture = gi->textures[t_idx];
	// static int j;

	double times2print = (double)line_height / (double)texture->height;
	int texture_column/*  = x % texture->width */;

	if (prev_texture != t_idx)
		texture_offset = 0;
	texture_column = texture_offset;


/*  	if (!(j % 10))
	{
		printf("texture: %s\n",gi->map_info->texture_paths[t_idx]);
		printf("times2print %f, line_height = %d\n",times2print, line_height);
		printf(" texture size %i x %i\n",texture->width, texture->height);
		// printf("max loops %i\n",texture->height / times2print * 4);
		printf("line_height %i\n",line_height );
		printf("txt column %i\n\n\n",texture_column );
	} */

	int bloc = 0; //max bloks = line_height / times2print
	int line_idx = 0;
	int	t;
	unsigned int px_to_print_idx = texture_column * 4;
	uint32_t px_to_print;
	// j = 0;
	while (px_to_print_idx <= ((texture->width * texture->height) - 1) * 4)
	{
		// j++;
		px_to_print = get(&(texture->pixels[px_to_print_idx]));
/* 		if (!(j % 10))
		{
			printf("line_idx %i\n", line_idx);
			printf("pixel_idx: %i\n", px_to_print_idx);
			printf("pixel color: %x\n\n", px_to_print);
}		 */

		t = bloc * times2print;
		while (t < ((bloc + 1) * times2print))
		{
			my_put_pixel(img,
			x,
			margin + t,
			px_to_print
			);
			t++;
		}
/* 		t = line_idx;
		while (t < line_height)
		{
			my_put_pixel(img,
			x,
			margin + t,
			px_to_print
			);
			t++;
		} */

		line_idx += times2print;
		px_to_print_idx += texture->width * 4;
		bloc++;
	}
	texture_offset = (texture_offset + 1) % texture->width;
	prev_texture = t_idx;
}
/* void print_texture(t_gameInfo	*gi,mlx_image_t	*img, int x, int margin, int line_height, int t_idx)
{
	mlx_texture_t *texture = gi->textures[t_idx];
	static int j;
	uint32_t px_to_print;
	int times2print = line_height / texture->height;
	int texture_column = x % texture->width;

	if (!j)
	{
		printf("times2print %i, line_height = %d\n",times2print , line_height);
		printf("txt column %i\n",texture_column );
	}

	int i = 0; //screen y
	int t = 0;
	// int g = 0; //texture y
	while (i < line_height - 19)
	{
		//pxX (texture_column)
		//pxY(t % times2print)

		if (!j)
		{
			printf("pixel: %i\n",((i / times2print * texture->height) + (texture_column)));
			printf("i: %i, text %i\n", i, ((i / times2print * texture->height) + (texture_column)) * 4);
		}
		px_to_print = get(&(texture->pixels[

			((i / times2print * texture->height) + (texture_column)) * 4

			]));
		t = -1;
		while (++t < times2print && i < line_height)
		{
			my_put_pixel(img,
			x,
			margin + i,
			px_to_print
			);
			i++;
		}
	}
	j = 1;
} */

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
	ang_incr = FOV / (double) gi->screen_w;
		// FILE * fp = fopen("log.log", "w+");
		FILE * fp = fopen("/dev/null", "w+");
 	while (++x < gi->screen_w)
	{
		fprintf(fp, "(player orientation = %d\n", gi->player->orientation);
		dis = get_dist(gi, gi->player->orientation + (FOV / 2) - (ang_incr * x), &texture, &fp);
		printed_height = round((32 * (gi->screen_w * 0.5 / tan(dtr(FOV / 2)))) / dis);
/* 		if (printed_height > gi->screen_h)
			printed_height = gi->screen_h; */
		margin = (gi->screen_h - printed_height) / 2;
			fprintf(fp, "dis =  %f, printed_height = %i, margin = %d\n", dis, printed_height, margin);
			fprintf(fp, "	dot1(x: %i y = %i), dot2(x = %d, y = %d). COLOUR = %d\n", x, margin, x, margin + printed_height, texture);
			fprintf(fp, "--------------------------------------------------------------------------------------------------------\n");
		// line(test, (double[2]){x, margin}, (double[2]){x, margin + printed_height}, texture);
		print_texture(gi, test,(int) x, margin, printed_height, texture);


	}
	return (test);
}

void draw_dot(t_gameInfo	*gi, double angle, int dis)
{
	double dot_x;
	double dot_y;

/* 	dot_x = (gi->player->x) + (dis * cos(dtr(angle)));
	dot_y = (gi->player->y) - (dis * sin(dtr(angle))); */

	dot_x = (gi->player->x + floor(gi->player_size / 2)) + (dis * cos(dtr(angle)));
	dot_y = (gi->player->y + floor(gi->player_size / 2)) - (dis * sin(dtr(angle)));
	if (dot_x < 1 || dot_x > gi->screen_w - 1 || dot_y < 1 || dot_y > gi->screen_h - 1)
		return ;
	my_put_pixel(gi->screen_image, (int) dot_x, (int) dot_y, 0x0000FFFF);

}
/*
void mark_pnt(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (x < 1 || x > gi->screen_w - 1 || y < 1 || y > gi->screen_h - 1)
		return ;
	my_put_pixel(img, x - 1, y - 1, color);
	my_put_pixel(img, x - 1, y, color);
	my_put_pixel(img, x - 1, y + 1, color);

	my_put_pixel(img, x, y - 1, color);
	my_put_pixel(img, x, y, color);
	my_put_pixel(img, x, y + 1, color);

	my_put_pixel(img, x + 1, y - 1, color);
	my_put_pixel(img, x + 1, y, color);
	my_put_pixel(img, x + 1, y + 1, color);

} */


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
	mlx_resize_hook(game_info->mlx, resize_hook, game_info);

	mlx_loop(game_info->mlx);
	mlx_terminate(game_info->mlx);
	return (EXIT_SUCCESS);
}

