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
#define	MINIMAP_WIDTH_FACTOR .2		// multiplied by WIDTH

#define BCKG_COLOR 0xFF			// black
#define WALL_COLOR 0xFFFFFFFF	// white
#define PLAYER_COLOR 0xFF0FF0FF	// red
/*
	player->x / Screen width == miniplayer->x / minimap_width
	player->y / Screen height == miniplayer->y / minimap_height

 */

void draw_minimap_texture (mlx_image_t *img, int pos[2], int size, uint32_t color)
{
	for (int y = 0; y < size; y ++)
	{
		for (int x = 0; x < size; x ++)
		{
			if (pos[0] + x < WIDTH && pos[1] + y < HEIGHT)
				mlx_put_pixel(img, pos[0] + x, pos[1] + y, color);
		}
	}
}

void draw_minimap (t_gameInfo	*gi, mlx_image_t *img, int pos[2])
{
	double map_w = gi->map_info->map_width * TEXTURE_SIZE;
	double map_h = gi->map_info->map_height * TEXTURE_SIZE;

	int	minimap_width = MINIMAP_WIDTH_FACTOR * WIDTH;

	int	bloc_size = minimap_width / gi->map_info->map_width;
	minimap_width = bloc_size * gi->map_info->map_width;
	int	minimap_height = bloc_size * gi->map_info->map_height;

	int bloc_x;
	int bloc_y;

	for (int y = 0; gi->map_info->map[y]; y ++)
	{
		bloc_y = pos[1] + (bloc_size * y);
		for (int x = 0; x < gi->map_info->map_width; x ++)
		{
			bloc_x = pos[0] + (bloc_size * x);

			if (gi->map_info->map[y][x] == '1')
				draw_minimap_texture (img, (int[2]){bloc_x, bloc_y},bloc_size, WALL_COLOR);
			else
				draw_minimap_texture (img, (int[2]){bloc_x, bloc_y},bloc_size, BCKG_COLOR);
		}
	}
	int miniplayer[2];
	miniplayer[0] = pos[0] + round((((double)gi->player->x / map_w)) * minimap_width);
	miniplayer[1] = pos[1] + round((((double)gi->player->y / map_h)) * minimap_height);

	int	miniplayer_end[2];
	miniplayer_end[0] = miniplayer[0] + (int)round (cos(dtr(gi->player->orientation)) * 10);
	miniplayer_end[1] = miniplayer[1] - (int)round (sin(dtr(gi->player->orientation)) * 10);

	mark_pnt(img, miniplayer[0], miniplayer[1],	PLAYER_COLOR);
 	// printf("\n\nangle: %i, cos: %f, sin: %f\n", gi->player->orientation, cos(dtr(gi->player->orientation)), sin(dtr(gi->player->orientation)));
	// printf(" x: %i, y: %i\n",
	// 	(int)round(miniplayer[0]),
	// 	(int)round(miniplayer[1]));
	// printf(" new x: %i, new y: %i\n", miniplayer_end[0], miniplayer_end[1]);
	line(img, miniplayer, miniplayer_end, -1);
	/* 	printf("minimap_width: %i, minimap_height %i\n",minimap_width, minimap_height);
		printf("player xy: %i, %i\n",gi->player->x, gi->player->y);
		printf("miniplayer xy: %i, %i\n",miniplayer[0], miniplayer[1]);
		printf("pos: %i, %i\n",pos[0], pos[1]);
		printf("finale miniplayer xy: %i, %i\n",pos[0] + miniplayer[0], pos[1] + miniplayer[1]);
		printf("\n"); */

}
/*
	(player->x / Screen width)  * minimap_width== miniplayer->x
	player->y / Screen height == miniplayer->y / minimap_height

 */