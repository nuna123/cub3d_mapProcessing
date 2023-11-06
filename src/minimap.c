/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:11:08 by nroth             #+#    #+#             */
/*   Updated: 2023/10/18 18:57:28 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	draw_minimap_texture(mlx_image_t *img, double pos[2],
		int size, uint32_t color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < size)
	{
		x = -1;
		while (++x < size)
		{
			if (pos[0] + x < img->width && pos[1] + y < img->height)
				my_put_pixel(img, round(pos[0] + x),
					round(pos[1] + y), color);
		}
	}
}

/*
	the initial minimap width depends on the screen width, it will be equal
		to gi->screen_w * width factor	then the minimap bloc size is calculated based
		on the minimap width and the amount of blocks it needs to
		fit (gi->map_info->map_width)
	minimap height is based on the block size and the amount of blocks in the
		height of the map (gi->map_info->map_height)

	to calculate miniplayer position:
			player_pos				miniplayer_pos
		-----------------	==	----------------------
			total_map_width			total_minimap_width
 */
	// int		minimap_width;
	// int		minimap_height;
	// minimap_width = bloc_size * gi->map_info->map_width;
	// int	minimap_height = bloc_size * gi->map_info->map_height;

static void	print_minimap(t_gameInfo *gi, mlx_image_t *img,
	int pos[2], int bloc_size)
{
	double	bloc[2];
	int		map_pos[2];

	map_pos[1] = -1;
	while (gi->map_info->map[++map_pos[1]])
	{
		bloc[1] = pos[1] + (bloc_size * map_pos[1]);
		map_pos[0] = -1;
		while (gi->map_info->map[map_pos[1]][++map_pos[0]])
		{
			bloc[0] = pos[0] + (bloc_size * map_pos[0]);
			if (gi->map_info->map[map_pos[1]][map_pos[0]] == '1')
				draw_minimap_texture (img, bloc, bloc_size, WALL_COLOR);
			else
				draw_minimap_texture (img, bloc, bloc_size, BCKG_COLOR);
		}
	}
}

void	draw_minimap(t_gameInfo *gi, mlx_image_t *img, int pos[2])
{
	double	mini_pl[2];
	double	mini_pl_end[2];
	int		bloc_size;

	bloc_size = (MINIMAP_WIDTH_FACTOR * gi->screen_w) / gi->map_info->map_width;
	print_minimap(gi, img, pos, bloc_size);
	mini_pl[0] = pos[0] + round(
			(double)gi->player->x / (gi->map_info->map_width * gi->txtr_size)
			* (bloc_size * gi->map_info->map_width));
	mini_pl[1] = pos[1] + round(
			(double)gi->player->y / (gi->map_info->map_height * gi->txtr_size)
			* (bloc_size * gi->map_info->map_height));
	mini_pl_end[0] = mini_pl[0] + round (cos(dtr(gi->player->angle)) * 10)
		+ (bloc_size / 4);
	mini_pl_end[1] = mini_pl[1] - round (sin(dtr(gi->player->angle)) * 10)
		+ (bloc_size / 4);
	draw_minimap_texture (img, mini_pl, bloc_size / 2, PLAYER_COLOR);
	mini_pl[0] += (bloc_size / 4);
	mini_pl[1] += (bloc_size / 4);
	line(img, mini_pl, mini_pl_end, PLAYER_COLOR);
}
