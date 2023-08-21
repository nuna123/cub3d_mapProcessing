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

static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

void	closeme(void	*map_info)
{
	t_mapInfo	*mi;
	mi = map_info;
	map_info_free(mi);
}
void	closeme_key(mlx_key_data_t keydata, void	*map_info)
{
	t_mapInfo	*mi;
	mi = map_info;
	if(keydata.key == MLX_KEY_ESCAPE)
	{
		map_info_free(mi);
		mlx_terminate(mlx);
		exit(1);
	}

}

int main(int argc, char *argv[])
{
	char		*map_path;
	t_mapInfo	*map_info;
	mlx_t		*mlx;

	if (argc > 1)
		map_path = argv[1];
	else
		return (printf("Error!\nNo map path specified.\n"), 1);
	map_info = get_map(map_path);
	if (!map_info)
		return (1);
	mlx = mlx_init(map_info->map_width * 32, map_info->map_height * 32, "42Balls", true);
	if (!mlx)
		exit(-1);

	// map_info_free(map_info);

	mlx_close_hook(mlx, closeme, map_info );
	mlx_key_hook(mlx, closeme_key, map_info);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);

	return (0);
}