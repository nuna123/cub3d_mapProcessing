/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:11:08 by nroth             #+#    #+#             */
/*   Updated: 2023/11/10 16:33:33 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	line(mlx_image_t *img, double a[2], double b[2], uint32_t color)
{
	double		steps[2];
	double		c[2];
	double		max;

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
	int			scrn_half;

	test = mlx_new_image(gi->mlx, WIDTH, HEIGHT);
	if (!test)
		return (NULL);
	scrn_half = HEIGHT / 2;
	y = -1;
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
		{
			my_put_pixel(test, x, y, gi->map_info->ceiling_color);
			my_put_pixel(test, x, y + scrn_half, gi->map_info->floor_color);
		}
	}
	return (test);
}

//vals[0] = x coordinate, vals[1] = margin, vals[2] = line height
//px2print[0]= index of pixel in the texture, [1] = actual pixel color info
//texture_offset = texture offset, gets reset every time
//		function passes to new texture.
//prev_texture = flag to keep track of previous texture
// iters[3] ->	[0] = how many times to print each texture pixle
//				[1] = keep track of how many txtr pixels have been printed
//				[2] = a lil counter

void	print_texture(t_gameInfo *gi, mlx_image_t *img, int vals[3], int t_idx)
{
	static int		texture_offset;
	static int		prev_texture = -1;
	mlx_texture_t	*texture;
	uint32_t		px2print[2];
	double			iters[3];

	texture = gi->textures[t_idx];
	iters[0] = (double)vals[2] / (double)texture->height;
	if (prev_texture != t_idx)
		texture_offset = 0;
	px2print[0] = texture_offset * 4;
	iters[1] = 0;
	while (px2print[0] <= ((texture->width * texture->height) - 1) * 4)
	{
		px2print[1] = get(&(texture->pixels[px2print[0]]));
		iters[2] = iters[1] * iters[0];
		while (iters[2] < ((iters[1] + 1) * iters[0]))
			my_put_pixel(img, vals[0], vals[1] + (iters[2]++), px2print[1]);
		px2print[0] += texture->width * 4;
		iters[1]++;
	}
	texture_offset = (texture_offset + 1) % texture->width;
	prev_texture = t_idx;
}

// textures indices: 0 east , 1 north, 2 west, 3 south
mlx_image_t	*create_screen_image(t_gameInfo	*gi)
{
	mlx_image_t	*test;
	int			x;
	double		dis;
	int			printed_height;
	int			texture;

	x = -1;
	test = print_bcg(gi);
	if (!test)
		return (NULL);
	while (++x < WIDTH)
	{
		dis = get_dist(gi,
				gi->player->angle + (FOV / 2)
				- ((FOV / (double) WIDTH) * x) - gi->offset,
				&texture);
		printed_height = round(
				(32 * (WIDTH * 0.5 / tan(dtr(FOV / 2)))) / dis);
		print_texture(gi, test, (int [3])
		{x, (HEIGHT - printed_height) / 2, printed_height}, texture);
	}
	return (test);
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

	mlx_image_to_window(gi->mlx, gi->screen_image, 0, 0);
	get_stars(gi);
	get_star_img(gi);
	get_minimap_img(gi);
	get_txt_img(gi);
}
