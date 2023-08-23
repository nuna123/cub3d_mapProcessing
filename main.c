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

#define WIDTH 1500
#define HEIGHT 840

void	print_screen (t_gameInfo *game_info)
{
	for (int x = 0; x < game_info->map_info->map_height; x++)
	{
		char *line = game_info->map_info->map[x];
		for (int i = 0; line[i]; i++)
		{
			if (line[i] == '1')
				mlx_image_to_window(game_info->mlx, game_info->wall_image, i * game_info->image_size, x * game_info->image_size);
			else if (line[i] == 'P')
				line[i] = '0';
			else
				mlx_image_to_window(game_info->mlx, game_info->bckg_image, i * game_info->image_size, x * game_info->image_size);
		}
	}
	mlx_image_to_window(game_info->mlx, game_info->player_image, game_info->player->x, game_info->player->y);
}

int	get_image_size (t_mapInfo *mi)
{
 	if (WIDTH / mi->map_width < HEIGHT / mi->map_height)
		return (WIDTH / mi->map_width);
	return (HEIGHT / mi->map_height);
/* 	if (mi->map_height < mi->map_width)
		return (mi->map_height);
	return (mi->map_width); */
}

mlx_image_t	*make_color_image(t_gameInfo *gi, uint32_t color)
{
	mlx_image_t	*new_image;
	int			size;
	int			counter;
	int			counter2;

	size = get_image_size(gi->map_info);
	new_image = mlx_new_image(gi->mlx, size, size);
	counter = -1;
	while (++counter < size)
	{
		counter2 = -1;
		while (++counter2 < size)
			mlx_put_pixel(new_image, counter, counter2, color);
	}
	return (new_image);
}

void	free_gameInfo(t_gameInfo *gi)
{
	free(gi->player);
	map_info_free(gi->map_info);
	mlx_delete_image(gi->mlx, gi->bckg_image);
	mlx_delete_image(gi->mlx, gi->wall_image);
	mlx_delete_image(gi->mlx, gi->player_image);
	mlx_terminate(gi->mlx);
	free(gi);
}

void	player_rotate(t_gameInfo *gi, int orientation)
{
	if (orientation == MLX_KEY_RIGHT)
		gi->player->orientation = (360 + gi->player->orientation + 45) % 360;
	else
		gi->player->orientation = (360 + gi->player->orientation - 45) % 360;

	printf("PLAYER DIRECTION {%i}\n", gi->player->orientation);
}

void	change_x_y(int x, int y, t_gameInfo *gi)
{
	int player_x = ((gi->player->x + x) / gi->image_size) + 1;
	int player_y = ((gi->player->y + y) / gi->image_size) + 1;

	// printf("INIT x: %i, y: %i\n", gi->player->x, player_);
	printf("x: %i, y: %i\n", player_x, player_y);

	if (gi->map_info->map[player_y][player_x] != '0')
		printf("BUMP WALL\n");
	else
	{
		mlx_image_to_window(gi->mlx, gi->bckg_image, gi->player->x, gi->player->y);
		gi->player->x += x;
		gi->player->y += y;
		mlx_image_to_window(gi->mlx, gi->player_image, gi->player->x, gi->player->y);
	}
}



void	player_move(t_gameInfo *gi, int direction)
{
	if (direction == 0)
		direction = -10;
	else
		direction = 10;


	if (gi->player->orientation >= 270 + 45  || gi->player->orientation <= 90 - 45)
		change_x_y(0, direction * -1, gi);
	else if(gi->player->orientation >= 90 + 45 && gi->player->orientation <= 270 - 45)
		change_x_y(0, direction, gi);

	if (gi->player->orientation >= 180 + 45  && gi->player->orientation <= 360 - 45)
		change_x_y(direction * -1, 0, gi);
	else if(gi->player->orientation >= 0 + 45 && gi->player->orientation <= 180 - 45)
		change_x_y(direction, 0, gi);
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
void	key_hooker(mlx_key_data_t keydata, void	*game_info)
{

	//	MLX_KEY_RIGHT			= 262
	// 	MLX_KEY_LEFT			= 263
	// 	MLX_KEY_DOWN			= 264
	// 	MLX_KEY_UP				= 265

	if(keydata.key == MLX_KEY_ESCAPE)
		closeme(game_info);
	else if (keydata.action)
	{
		if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
			player_rotate((t_gameInfo *) game_info, keydata.key);
		else if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN)
			player_move((t_gameInfo *) game_info, keydata.key - MLX_KEY_DOWN);
	}
}

t_player	*get_player(t_mapInfo *mapInfo)
{
	int			x;
	int			y;
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return NULL;
	y = -1;
	while (++y < mapInfo->map_height)
	{
		x = -1;
		while (mapInfo->map[y][++x])
		{
			if (ft_strchr("NSWE", mapInfo->map[y][x]))
			{
				player->x = x * get_image_size(mapInfo);
				player->y = y * get_image_size(mapInfo);
				if (mapInfo->map[y][x] == 'N')
					player->orientation = 0;
				else if (mapInfo->map[y][x] == 'S')
					player->orientation = 180;
				else if (mapInfo->map[y][x] == 'E')
					player->orientation = 90;
				else if (mapInfo->map[y][x] == 'W')
					player->orientation = 270;
				mapInfo->map[y][x] = 'P';
				return (player);
			}
		}
	}
	return (free(player), NULL);
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
	game_info->mlx = mlx_init(WIDTH,HEIGHT, "blah", true);
	if (!game_info->mlx)
		return(map_info_free(game_info->map_info), free(game_info), NULL);

	game_info->player = get_player(game_info->map_info);
	if (!game_info->player)
		return(map_info_free(game_info->map_info), free(game_info), NULL);


	game_info->bckg_image = make_color_image(game_info, 0x000000FF);
	game_info->wall_image = make_color_image(game_info, 0xFFFFFFFF);
	game_info->player_image = make_color_image(game_info, 0xFF0000FF);

	game_info->image_size = get_image_size(game_info->map_info);


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

	int size = get_image_size(game_info->map_info);
	printf ("Map width: %i\nMap height: %i\nimage size: %i\n",
		game_info->map_info->map_width,
		game_info->map_info->map_height,
		game_info->image_size);
	printf ("\nplayer x: %i\nplayer y: %i\norientation: %i\n",
		game_info->player->x,
		game_info->player->y,
		game_info->player->orientation);


	print_screen(game_info);

	mlx_close_hook(game_info->mlx, closeme, game_info);
	mlx_key_hook(game_info->mlx, key_hooker, game_info);

	mlx_loop(game_info->mlx);
	mlx_terminate(game_info->mlx);
	return (EXIT_SUCCESS);
}