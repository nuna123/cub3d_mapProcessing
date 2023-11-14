/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:41:18 by ymorozov          #+#    #+#             */
/*   Updated: 2023/11/14 14:46:01 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

char	obj_xy_inmap(t_gameInfo *gi, int x, int y, int *id)
{
	if (x < 0 || y < 0)
		return (-1);
	if (y / gi->txtr_size >= gi->map_info->map_height
		|| x / gi->txtr_size >= gi->map_info->map_width)
		return (-1);
	*id = ((y / gi->txtr_size) * gi->map_info->map_width) + (x / gi->txtr_size);
	return (gi->map_info->map
		[(y / gi->txtr_size)]
		[(x / gi->txtr_size)]);
}

t_star	*make_new_star(int x, int y, int width, int height)
{
	t_star	*new_star;

	new_star = ft_calloc(sizeof(t_star), 1);
	if (!new_star)
		return (NULL);
	new_star->x = x;
	new_star->y = y;
	new_star->width = width;
	new_star->height = height;
	return (new_star);
}

void	get_txt_img(t_gameInfo *gi)
{
	mlx_image_t	*temp_image;
	char		*str;
	char		*tmp;

	if (gi->score == gi->map_info->star_count)
		str = ft_strdup("YOU WON!");
	else
	{
		tmp = ft_itoa(gi->score);
		str = ft_strjoin("SCORE: ", tmp);
		free(tmp);
		str = str_append(str, " / ", NULL);
		tmp = ft_itoa(gi->map_info->star_count);
		str = str_append(str, tmp, NULL);
		free(tmp);
	}
	temp_image = mlx_put_string(gi->mlx, str, WIDTH - 200, HEIGHT - 50);
	free(str);
	if (!temp_image)
		return ;
	if (gi->txt_image)
		mlx_delete_image(gi->mlx, gi->txt_image);
	gi->txt_image = temp_image;
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
