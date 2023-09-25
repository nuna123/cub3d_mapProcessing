/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:11:08 by nroth             #+#    #+#             */
/*   Updated: 2023/08/21 17:11:09 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	print_screen(t_gameInfo *game_info)
{
	for (int x = 0; x < game_info->map_info->map_height; x++)
	{
		char *line = game_info->map_info->map[x];
		for (int i = 0; line[i]; i++)
		{
			if (line[i] == '1')
				mlx_image_to_window(game_info->mlx, game_info->wall_image,
					i * game_info->image_size, x * game_info->image_size);
			else if (line[i] == 'P')
				line[i--] = '0';
			else
				mlx_image_to_window(game_info->mlx, game_info->bckg_image,
					i * game_info->image_size, x * game_info->image_size);
		}
	}
	mlx_image_to_window(game_info->mlx, game_info->player_image,
		game_info->player->x, game_info->player->y);
}

int	main(int argc, char *argv[])
{
	t_gameInfo	*game_info;

	if (argc <= 1)
		return (printf("Error!\nNo map path specified.\n"), 1);
	game_info = init_game_info(argv);
	if (!game_info)
		exit(-1);
	print_screen(game_info);
	mlx_close_hook(game_info->mlx, closeme, game_info);
	mlx_key_hook(game_info->mlx, key_hooker, game_info);
	mlx_loop(game_info->mlx);
	mlx_terminate(game_info->mlx);
	return (EXIT_SUCCESS);
}
	// printf ("Map width: %i\nMap height: %i\nimage size: %i\n",
	// 	game_info->map_info->map_width,
	// 	game_info->map_info->map_height,
	// 	game_info->image_size);
	// printf ("\nplayer x: %i\nplayer y: %i\norientation: %i\n",
	// 	game_info->player->x,
	// 	game_info->player->y,
	// 	game_info->player->orientation);