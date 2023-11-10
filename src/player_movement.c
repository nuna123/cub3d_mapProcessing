/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:25:56 by nroth             #+#    #+#             */
/*   Updated: 2023/10/17 17:31:37 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	update_player(t_gameInfo *gi, int x, int y)
{
	gi->player->x += x;
	gi->player->y += y;
	print_screen (gi);
}

void	player_rotate(t_gameInfo *gi, int angle)
{
	if (angle == MLX_KEY_RIGHT)
		gi->player->angle = (360 + gi->player->angle - 10) % 360;
	else
		gi->player->angle = (360 + gi->player->angle + 10) % 360;
	print_screen (gi);
	printf ("player direction : %i°\n", gi->player->angle);
}

//int direction is one of 4:
// D = 0, W = 1, A = 2, S = 3
static t_mapchar	check4pnts(t_gameInfo *gi, int player_x, int player_y)
{
	int	i;
	int	x;
	int	y;

	i = -3;
	while (++i < 3)
	{
		x = ((player_x) + ((i > 0) * gi->player_size));
		y = ((player_y) + ((i && !(i % 2)) * gi->player_size));
		if (coors_in_map(gi, x, y) == '1')
			return (WALL);
		if (coors_in_map(gi, x, y) == 'C')
		{/* //check position is within collectible bounds
			if ((x % gi->txtr_size > ((gi->txtr_size - (gi->txtr_size / 2)) / 2)
				&& x % gi->txtr_size < gi->txtr_size - ((gi->txtr_size - (gi->txtr_size / 2)) / 2))
			&& (y % gi->txtr_size > ((gi->txtr_size - (gi->txtr_size / 2)) / 2)
				&& y % gi->txtr_size < gi->txtr_size - ((gi->txtr_size - (gi->txtr_size / 2)) / 2)))
			{ */
				gi->map_info->map
				[(int)round (y / gi->txtr_size)]
				[(int)round (x / gi->txtr_size)] = '0';
				gi->score ++;
				printf("***COLLECTIBLE SCORE %i***\n", gi->score);
				return (COLLECTIBLE);
			// }
		}
	}
	return (SPACE);
}

void	move_player(t_gameInfo *gi, int dir)
{
	double		movement_angle;
	int			new_x;
	int			new_y;

	movement_angle = fmod (gi->player->angle + (90 * dir) + 360, 360);
	new_x = (int) round (cos(dtr(movement_angle)) * 10);
	new_y = (int) round (sin(dtr(movement_angle)) * -10);
	while (new_x
		&& check4pnts(gi, gi->player->x + new_x, gi->player->y) == WALL)
		new_x += -(new_x > 0) +(new_x < 0);
	while (new_y
		&& check4pnts(gi, gi->player->x, gi->player->y + new_y) == WALL)
		new_y += -(new_y > 0) +(new_y < 0);
	update_player(gi, new_x, new_y);
}
