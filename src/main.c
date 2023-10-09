/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:11:08 by nroth             #+#    #+#             */
/*   Updated: 2023/10/05 17:31:05 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

///TODO
	// deg to radians

uint32_t get(uint8_t * texture_pixels)
{
	uint32_t res  = 0;
	res += texture_pixels[0] << 24;
	res += texture_pixels[1] << 16;
	res += texture_pixels[2] << 8;
	res += texture_pixels[3];

	return res;
}

void print_texture(mlx_image_t *img, mlx_texture_t *texture, int coor_x, int coor_y)
{

	int pixel;
	for (uint32_t y = 0; y < texture->height; y++)
	{
		for (uint32_t x = 0; x < texture->width; x++)
		{
			pixel = (y * texture->height + x) * 4;
			mlx_put_pixel(img, (coor_x + x), (coor_y + y), get(&texture->pixels[pixel]));
		}
	}
}

mlx_image_t	*create_screen_image(t_gameInfo	*gi)
{
	mlx_image_t	*test;

	test = mlx_new_image(gi->mlx, WIDTH, HEIGHT);
	if (!test)
		return NULL;
	ft_memset(test->pixels, 255, test->width * test->height * sizeof(int32_t));
	for(int y = 0; gi->map_info->map[y]; y++)
	{
		for(int x = 0; gi->map_info->map[y][x]; x++)
		{
			if (gi->map_info->map[y][x] == '1')
				print_texture(test, gi->wall_texture, TEXTURE_SIZE * x,TEXTURE_SIZE *  y);
			else if (gi->map_info->map[y][x] == '0')
				print_texture(test, gi->bckg_texture, TEXTURE_SIZE * x,TEXTURE_SIZE *  y);
		}
	}
	print_texture(test, gi->player_texture, gi->player->x, gi->player->y);
	
	return test;
}


void	print_screen(t_gameInfo *game_info)
{
	mlx_image_t *img;
	img = create_screen_image(game_info);
	if (!img)
	{
		printf("ERR printscreen\n");
		return;
	}
	mlx_delete_image(game_info->mlx, game_info->screen_image);
	game_info->screen_image = img;
	mlx_image_to_window(game_info->mlx, game_info->screen_image, 0, 0);
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
