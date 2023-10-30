/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:25:39 by nroth             #+#    #+#             */
/*   Updated: 2023/09/25 13:25:40 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	closeme(void	*game_info)
{
	t_gameInfo	*gi;
	mlx_t		*mlx;

	gi = game_info;
	mlx = gi->mlx;
	free_game_info(gi);
	mlx_close_window(mlx);
	exit(0);
}
//	MLX_KEY_RIGHT			= 262
// 	MLX_KEY_LEFT			= 263
// 	MLX_KEY_DOWN			= 264
// 	MLX_KEY_UP				= 265

// D = 0, W = 1, A = 2, S = 3

void	key_hooker(mlx_key_data_t keydata, void	*gi)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		closeme(gi);
	else if (keydata.action)
	{
		if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
			player_rotate((t_gameInfo *) gi, keydata.key);
		else if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
			move_player((t_gameInfo *) gi, 0);
		else if (keydata.key == MLX_KEY_A)
			move_player((t_gameInfo *) gi, 1);
		else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
			move_player((t_gameInfo *) gi, 2);
		else if (keydata.key == MLX_KEY_D)
			move_player((t_gameInfo *) gi, 3);
	}
}
