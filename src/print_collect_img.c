/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_collect_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:23:37 by ymorozov          #+#    #+#             */
/*   Updated: 2023/11/10 18:26:34 by ymorozov         ###   ########.fr       */
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

//t2p[0] - width [times to print]
//t2p[1] - height [times to print]
//marg[0] - margin width
//marg[1] - margin height

static void	star_print(t_gameInfo *gi, t_star *star)
{
	int			t2p[2];
	int			marg[2];
	int			txtr_c[2];
	uint32_t	clr;

	t2p[0] = star->width / gi->star_texture[0]->width;
	if (t2p[0] < 1)
		t2p[0] = 1;
	t2p[1] = star->height / gi->star_texture[0]->height;
	if (t2p[1] < 1)
		t2p[1] = 1;
	marg[0] = star->width - (gi->star_texture[0]->width * t2p[0]);
	marg[1] = star->height - (gi->star_texture[0]->height * t2p[1]);
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

void	get_star_img(t_gameInfo *gi)
{
	int	i;

	mlx_delete_image(gi->mlx, gi->stars_image);
	gi->stars_image = mlx_new_image(gi->mlx, WIDTH, HEIGHT);
	if (gi->stars)
	{
		i = -1;
		while (gi->stars[++i])
			star_print(gi, gi->stars[i]);
	}
	mlx_image_to_window(gi->mlx, gi->stars_image, 0, 0);
}

void	get_stars(t_gameInfo *gi)
{
	t_star	**stars;
	int		x;
	double	dis;
	double	star_c;
	int		unused;

	x = -1;
	stars = NULL;
	star_c = 0;
	while (++x < WIDTH)
	{
		dis = star_get_dist(gi,
				gi->player->angle + (FOV / 2)
				- ((FOV / (double) WIDTH) * x) - gi->offset, &unused);
		if ((star_c == -1 || star_c == 0) && dis != -1)
			get_star(gi, x, &stars);
		if (star_c != -1 && dis == -1)
			star_c = 0;
		star_c = dis;
	}
	if (gi->stars)
		ft_arrfree((void **) gi->stars);
	gi->stars = stars;
}
