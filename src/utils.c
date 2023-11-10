/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:25:39 by nroth             #+#    #+#             */
/*   Updated: 2023/09/25 13:25:40 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
// DEGREES TO RADIANS
double	dtr(double deg)
{
	return (deg * (M_PI / 180));
}

void	my_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x < img->width && y < img->height)
		mlx_put_pixel(img, x, y, color);
}
//	0				-	TEXTURE SIZE - 1		-> Block 0
//	TEXTURE SIZE	-	(TEXTURE SIZE * 2) - 1	-> Block 1
//	TEXTURE SIZE*2	-	(TEXTURE SIZE * 3) - 1	-> Block 2

char	coors_in_map(t_gameInfo *gi, int x, int y)
{
	if (x < 0 || y < 0)
		return (printf("1ERR! %i, %i\n", x, y), -1);
	if (y / gi->txtr_size >= gi->map_info->map_height
		|| x / gi->txtr_size >= gi->map_info->map_width)
		return (printf("2ERR! %i, %i\n\n", x, y), -1);
	// printf("\tBLOCK CHECKED  %i, %i (%i)\n", (x / gi->txtr_size), (y / gi->txtr_size), (y) + (x / gi->txtr_size));
	return (gi->map_info->map
		[(y / gi->txtr_size)]
		[(x / gi->txtr_size)]);
}

void	define_texture(double horiz_dis, double vert_dis,
		double angle, int *txtr)
{
	double	new_ang;

	new_ang = fmod((angle + 360), 360);
	if (vert_dis == horiz_dis)
		vert_dis = -1;
	if ((new_ang < 90 || new_ang > 270)
		&& (vert_dis == -1 || horiz_dis < vert_dis))
		*txtr = 0;
	else if ((new_ang > 0 && new_ang < 180)
		&& (horiz_dis == -1 || horiz_dis > vert_dis))
		*txtr = 1;
	else if ((new_ang > 90 && new_ang < 270)
		&& (vert_dis == -1 || horiz_dis < vert_dis))
		*txtr = 2;
	else if ((new_ang > 180 && new_ang < 360)
		&& (horiz_dis == -1 || horiz_dis > vert_dis))
		*txtr = 3;
}

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
