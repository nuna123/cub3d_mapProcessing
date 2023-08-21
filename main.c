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

void	free_gameInfo(t_gameInfo *gi)
{
	map_info_free(gi->map_info);
	free(gi);
}





void	closeme(void	*game_info)
{
	t_gameInfo	*gi;
	mlx_t		*mlx;

	gi = game_info;
	mlx = gi->mlx;
	free_gameInfo(gi);
	mlx_close_window(mlx);

	exit(0);
}
void	closeme_key(mlx_key_data_t keydata, void	*game_info)
{
	if(keydata.key == MLX_KEY_ESCAPE)
	{
		closeme(game_info);
	}

}

t_gameInfo	*init_gameInfo(char *argv[])
{
	t_gameInfo	*game_info;

	game_info = ft_calloc(1, sizeof(t_gameInfo));
	if (!game_info)
		return (NULL);
	game_info->map_info = get_map(argv[1]);
	if (!game_info->map_info)
		return (free(game_info), NULL);
	game_info->mlx = mlx_init(game_info->map_info->map_width * 32,game_info->map_info->map_height * 32, "42Balls", true);
	if (!game_info->mlx)
		return(map_info_free(game_info->map_info), free(game_info), NULL);

	return (game_info);
}

int main(int argc, char *argv[])
{

	t_gameInfo	*game_info;

	if (argc <= 1)
		return (printf("Error!\nNo map path specified.\n"), 1);

	game_info = init_gameInfo(argv);
	if (!game_info)
		exit(-1);

	mlx_close_hook(game_info->mlx, closeme, game_info);
	mlx_key_hook(game_info->mlx, closeme_key, game_info);

	mlx_loop(game_info->mlx);
	mlx_terminate(game_info->mlx);
	return (EXIT_SUCCESS);
}