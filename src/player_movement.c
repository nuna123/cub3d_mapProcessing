/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliamorozova <yuliamorozova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:25:56 by nroth             #+#    #+#             */
/*   Updated: 2023/10/09 15:55:42 by yuliamorozo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"



// returns the map char at position (x, y)
char	coors_in_map(t_gameInfo *gi, int x, int y)
{
	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT)
		return (0);

/* 	printf("xy: %i(%i), %i (%i)\n", x, x % TEXTURE_SIZE, y, y % TEXTURE_SIZE);
	printf("BLOC: %i, %i\n", x / TEXTURE_SIZE, y / TEXTURE_SIZE); */
	return (gi->map_info->map
		[y / TEXTURE_SIZE]
		[x / TEXTURE_SIZE]);
}

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
		if (player_x % TEXTURE_SIZE != 0 || player_y % TEXTURE_SIZE != 0)
		{
			if (coors_in_map(gi, player_x, player_y) != '0')
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
		gi->player->orientation = (360 + gi->player->orientation - 45) % 360;
	else
		gi->player->orientation = (360 + gi->player->orientation + 45) % 360;
	printf("player direction : %i°\n", gi->player->orientation);
}


#define NORTH 90
#define EAST 0
#define SOUTH 180
#define WEST 270
// 1 = UP; 0 = DOWN
// if statements define the N, S, WE and EA areas in order
void	player_move(t_gameInfo *gi, int direction)
{
	if (direction == 0)
		direction = -10;
	else
		direction = 10;
	if (gi->player->orientation < 180 && gi->player->orientation > 0) //NORTH SECTION
		change_x_y(0, direction * -1, gi);
	else if (gi->player->orientation > 180 && gi->player->orientation < 360) //SOUTH SECTION
		change_x_y(0, direction, gi);

	if (gi->player->orientation > 90 && gi->player->orientation < 270) //WEST
		change_x_y(direction * -1, 0, gi);
	else if (gi->player->orientation > 270 || gi->player->orientation < 90) // EAST
		change_x_y(direction, 0, gi);
}
