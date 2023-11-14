/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_collect_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:23:37 by ymorozov          #+#    #+#             */
/*   Updated: 2023/11/14 14:03:31 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

//w_h[0] - width
//w_h[1] - height

static void	print_bloc(mlx_image_t *img, uint32_t color, int coors[2], int *w_h)
{
	int	x;
	int	y;

	y = -1;
	while (++y < w_h[1])
	{
		x = -1;
		while (++x < w_h[0])
			my_put_pixel(img, x + coors[0], y + coors[1], color);
	}
}

static uint32_t	get_color(mlx_texture_t *txtr, int x, int y)
{
	return (get(&txtr->pixels[(y * txtr->width + x) * 4]));
}

// t2p[0] - width [times to print]
// t2p[1] - height [times to print]
// marg[0] - margin width
// marg[1] - margin height

static void	print_small_star(t_gameInfo *gi, t_star *star)
{
	int			x;
	int			starx;
	int			y;
	uint32_t	clr;

	y = -1;
	while (++y < (int)gi->star_texture[0]->height)
	{
		x = gi->star_texture[0]->width - star->width - 1;
		starx = 0;
		while (++x < (int) gi->star_texture[0]->width)
		{
			clr = get_color(gi->star_texture[0], x, y);
			my_put_pixel(gi->stars_image, star->x + starx, star->y + y, clr);
			starx++;
		}
	}
}

static void	star_print_ext(t_gameInfo *gi, t_star *star, int *t2p, int *marg)
{
	t2p[0] = star->width / gi->star_texture[0]->width;
	t2p[1] = star->height / gi->star_texture[0]->height;
	marg[0] = star->width - (gi->star_texture[0]->width * t2p[0]);
	marg[1] = star->height - (gi->star_texture[0]->height * t2p[1]);
}

void	star_print(t_gameInfo *gi, t_star *star)
{
	int			t2p[2];
	int			marg[2];
	int			txtr_c[2];
	uint32_t	clr;

	if (star->width >= (int)gi->star_texture[0]->width)
	{
		star_print_ext(gi, star, t2p, marg);
		txtr_c[1] = -1;
		while (++txtr_c[1] < (int) gi->star_texture[0]->height)
		{
			txtr_c[0] = -1;
			while (++txtr_c[0] < (int) gi->star_texture[0]->width)
			{
				clr = get_color(gi->star_texture[0], txtr_c[0], txtr_c[1]);
				print_bloc(gi->stars_image, clr, (int [2]){txtr_c[0] * t2p[0]
					+ marg[0] + star->x, txtr_c[1] * t2p[1] + marg[1]
					+ star->y}, (int [2]){t2p[0], t2p[1]});
			}
		}
	}
	else
		print_small_star(gi, star);
}
