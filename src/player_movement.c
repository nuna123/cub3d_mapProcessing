/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:25:56 by nroth             #+#    #+#             */
/*   Updated: 2023/09/25 13:25:57 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	update_player(t_gameInfo *gi, int x, int y)
{
	gi->player->x += x;
	gi->player->y += y;
	print_screen (gi);
}

static int	change_x_y(int x, int y, t_gameInfo *gi)
{
	int	player_x;
	int	player_y;
	int	i;

	if (!x && !y)
		return (ERR);
	i = -3;
	while (++i < 3)
	{
		player_x = ((gi->player->x + x) + ((i > 0) * gi->player_size));
		player_y = ((gi->player->y + y) + ((i && !(i % 2)) * gi->player_size));
		if (player_x % gi->image_size != 0 || player_y % gi->image_size != 0)
		{
			if (gi->map_info->map[player_y / gi->image_size]
				[player_x / gi->image_size] != '0')
			{
				player_x = x + ((x <= 0) - 1) + (x < 0);
				player_y = y + ((y <= 0) - 1) + (y < 0);
				change_x_y(player_x, player_y, gi);
				return (ERR);
			}
		}
	}
	update_player (gi, x, y);
	return (OK);
}

void	player_rotate(t_gameInfo *gi, int orientation)
{
	if (orientation == MLX_KEY_RIGHT)
		gi->player->orientation = (360 + gi->player->orientation + 45) % 360;
	else
		gi->player->orientation = (360 + gi->player->orientation - 45) % 360;
	printf("PLAYER DIRECTION {%i}\n", gi->player->orientation);
}

// 1 = UP; 0 = DOWN
// if statements define the N, S, WE and EA areas in order
void	player_move(t_gameInfo *gi, int direction)
{
	if (direction == 0)
		direction = -10;
	else
		direction = 10;
	if (gi->player->orientation > 270 || gi->player->orientation < 90)
		change_x_y(0, direction * -1, gi);
	else if (gi->player->orientation > 90 && gi->player->orientation < 270)
		change_x_y(0, direction, gi);
	if (gi->player->orientation > 180 && gi->player->orientation < 360)
		change_x_y(direction * -1, 0, gi);
	else if (gi->player->orientation > 0 && gi->player->orientation < 180)
		change_x_y(direction, 0, gi);
}
