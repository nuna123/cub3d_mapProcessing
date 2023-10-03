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

# define PI 3.14159265

float deg_to_rad(int deg)
{
	return (deg * (PI / 180));
}

///TODO
	// change display function to create a image and display it each time
	// deg to radians
	// rgb to hex


//ASSUMING ROTATION IS 270 -> 90. facing upwards
void init_dot(t_gameInfo *gi)
{
	int	x_coor;
	int	y_coor;

	float a, b, c;

	// first loop to offset to bloc size (gi->image_size)
	x_coor = gi->player->x;
	y_coor = gi->player->y - (gi->player->y % gi->image_size);

	printf("xy: (%i, %i) char: %c\n", x_coor, y_coor, coors_in_map(gi, x_coor, y_coor - 1));

	a = (gi->player->y % gi->image_size);
	b = tan (deg_to_rad(gi->player->orientation)) * a;
	c = a / cos (deg_to_rad(gi->player->orientation));

	printf ("a: %f ; b: %f; c: %f\n", a, b, c);

}




/* void	create_screen_image(t_gameInfo	*gi)
{
	mlx_image_t	*test;

	test = mlx_new_image(gi->mlx, 2, 2);
	memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));

	if (!test)
		return ;

} */




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

	// init_dot(game_info);
}


int	main(int argc, char *argv[])
{
	t_gameInfo	*game_info;




	if (argc <= 1)
		return (printf("Error!\nNo map path specified.\n"), 1);
	game_info = init_game_info(argv);
	if (!game_info)
		exit(-1);


	// create_screen_image(game_info);

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