/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:25:50 by nroth             #+#    #+#             */
/*   Updated: 2023/09/25 13:25:51 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/*
	logic:
		'N' = 78; -> 0°
		'E' = 69; -> 90° = 90 * 1
		'S' = 83; -> 180° = 90 * 2
		'W' = 87; -> 270° = 90 * 3

		apart from N, the other directions are in ascending order.
		first 'IF' is to take care of that exception.
		subtracting 61 makes
			E = 8 (% 8 = 1),
			S = 22 (% 8 = 2),
			W = 26  (% 8 = 3)
 */
static t_player	*player_setup(t_gameInfo *gi, char *dir_c, int x, int y)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (NULL);
	player->x = (x * gi->image_size);
	player->y = (y * gi->image_size);
	if (*dir_c == 'N')
		player->orientation = 0;
	else
	{
		*(dir_c) -= 61;
		player->orientation = 90 * (*(dir_c) / 8);
	}
	*(dir_c) = '0';
	return (player);
}

t_player	*get_player(t_gameInfo *gi)
{
	int			x;
	int			y;

	y = -1;
	while (++y < gi->map_info->map_height)
	{
		x = -1;
		while (gi->map_info->map[y][++x])
		{
			if (ft_strchr("NSWE", gi->map_info->map[y][x]))
				return (player_setup(gi, &(gi->map_info->map[y][x]), x, y));
		}
	}
	return (NULL);
}
