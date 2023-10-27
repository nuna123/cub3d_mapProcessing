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
double dtr(double deg)
{
	return(deg * (M_PI / 180));
}
void	my_put_pixel(mlx_image_t* img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x < img->width && y < img->height)
		mlx_put_pixel(img, x, y, color);
}
char	coors_in_map(t_gameInfo *gi, int x, int y)
{
	if (x < 0 || y < 0 || x >= gi->screen_w || y >= gi->screen_h)
		return (0);
	if (y / gi->texture_size >= gi->map_info->map_height
		|| x / gi->texture_size >= gi->map_info->map_width)
		return (0);
	return (gi->map_info->map
		[(int)ceil (y / gi->texture_size)]
		[(int)ceil (x / gi->texture_size)]);
}