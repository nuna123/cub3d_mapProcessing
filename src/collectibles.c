/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:41:18 by ymorozov          #+#    #+#             */
/*   Updated: 2023/11/10 18:25:13 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

char	obj_xy_inmap(t_gameInfo *gi, int x, int y, int *id)
{
	if (x < 0 || y < 0)
		return (printf("1ERR! %i, %i\n", x, y), -1);
	if (y / gi->txtr_size >= gi->map_info->map_height
		|| x / gi->txtr_size >= gi->map_info->map_width)
		return (printf("2ERR! %i, %i\n\n", x, y), -1);
	*id = ((y / gi->txtr_size) * gi->map_info->map_width) + (x / gi->txtr_size);
	if(*id < 5)
		printf("!!!(%i, %i)!!!!!!!%i\n",x,y, *id);

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
		str = ft_strdup("LEVEL COMPLETE!");
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
	temp_image = mlx_put_string(gi->mlx, str ,WIDTH - 200 ,HEIGHT - 50);
	free(str);
	if (!temp_image)
		return ;
	if (gi->txt_image)
		mlx_delete_image(gi->mlx, gi->txt_image);
	gi->txt_image = temp_image;
}
