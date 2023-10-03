/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:25:33 by nroth             #+#    #+#             */
/*   Updated: 2023/09/25 13:25:34 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	get_image_size(t_mapInfo *mi)
{
	if (WIDTH / mi->map_width < HEIGHT / mi->map_height)
		return (WIDTH / mi->map_width);
	return (HEIGHT / mi->map_height);
}

static mlx_image_t	*make_color_image(t_gameInfo *gi, int size, uint32_t color)
{
	mlx_image_t	*new_image;
	int			counter;
	int			counter2;
	int c = 0;

	new_image = mlx_new_image(gi->mlx, size, size);
	counter = -1;

	printf("%i - %i -%i\n",new_image->width, new_image->height, new_image->width * new_image->height );

	while (++counter < size)
	{
		counter2 = -1;
		while (++counter2 < size)
		{
			mlx_put_pixel(new_image, counter2, counter, color);

			while (++c > (new_image->width * new_image->height * (sizeof(int32_t) / sizeof(int8_t))));
				printf(" - %i\n", c);
			/* printf("%i\t", new_image->pixels[counter * new_image->width + counter2]);

			if ((counter * new_image->width + counter2 + 1) % 4 == 0)
				printf(" - %i\n", c++); */
		}
	}
	return (new_image);
}

void	free_game_info(t_gameInfo *gi)
{
	free(gi->player);
	map_info_free(gi->map_info);
	mlx_delete_image(gi->mlx, gi->bckg_image);
	mlx_delete_image(gi->mlx, gi->wall_image);
	mlx_delete_image(gi->mlx, gi->player_image);
	mlx_terminate(gi->mlx);
	free(gi);
}

t_gameInfo	*init_game_info(char *argv[])
{
	t_gameInfo	*game_info;

	game_info = ft_calloc(1, sizeof(t_gameInfo));
	if (!game_info)
		return (NULL);
	game_info->map_info = get_map(argv[1]);
	if (!game_info->map_info)
		return (free(game_info), NULL);
	game_info->mlx = mlx_init(WIDTH, HEIGHT, "blah", true);
	if (!game_info->mlx)
		return (map_info_free(game_info->map_info), free(game_info), NULL);
	game_info->image_size = get_image_size(game_info->map_info);
	game_info->player_size = game_info->image_size * .5;
	game_info->player = get_player(game_info);
	if (!game_info->player)
		return (map_info_free(game_info->map_info), free(game_info), NULL);
/* 	game_info->bckg_image = make_color_image(game_info, game_info->image_size,
			0x000000FF);
	game_info->wall_image = make_color_image(game_info, game_info->image_size,
			0xFFFFFFFF); */
	game_info->player_image = make_color_image(game_info,
			game_info->player_size, 0xFF0000FF);

	mlx_delete_image(game_info->mlx, game_info->player_image);


	return (map_info_free(game_info->map_info), free(game_info), NULL);
	// return (game_info);
}
