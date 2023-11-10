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

void	our_mousefunc(mouse_key_t button, action_t action,
		modifier_key_t mods, void *game_info)
{
	int32_t		mousepos[2];
	t_gameInfo	*gi;

	(void) mods;
	gi = game_info;
	if (action != MLX_PRESS)
		return ;
	mlx_get_mouse_pos(gi->mlx, &mousepos[0], &mousepos[1]);
	if (button == MLX_MOUSE_BUTTON_MIDDLE)
		gi->offset = 5;
	else if (mousepos[0] < WIDTH / 2
		&& (gi->offset - 5) >= 0 - (FOV / 2))
		gi->offset -= 5;
	else if (mousepos[0] > WIDTH / 2 && (gi->offset + 5) <= (FOV / 2))
		gi->offset += 5;
	print_screen (gi);
}

void	loop_hook(void *game_info)
{
	t_gameInfo		*gi;
	static int		loop_count;
	mlx_texture_t	*temp;
	int				j;

	j = 20;
	loop_count ++;
	gi = (t_gameInfo *) game_info;
	if (loop_count % j != 0 || !gi->stars)
		return ;
	temp = gi->star_texture[0];
	gi->star_texture[0] = gi->star_texture[1];
	gi->star_texture[1] = temp;
	get_star_img(gi);
}
