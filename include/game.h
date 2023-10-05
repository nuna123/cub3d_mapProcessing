/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:11:15 by nroth             #+#    #+#             */
/*   Updated: 2023/08/21 17:11:16 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <math.h>


#include "libft.h"
#include "mapProcessing.h"
#include "MLX42.h"


#define WIDTH 1500
#define HEIGHT 840
#define TEXTURE_SIZE 32



#define PLAYER_PATH "../textures/droog.xpm42"

typedef struct s_player
{
	int	x; // top left corner's x position
	int	y; // top left corner's y position

	int	orientation; // where is it facing


} t_player;

typedef struct s_gameInfo
{
	mlx_t	*mlx;
	t_mapInfo	*map_info;

	mlx_texture_t	*bckg_texture;
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*player_texture;

	mlx_image_t	*screen_image;

	t_player	*player;

	int	image_size;
	int	player_size;
} t_gameInfo;

// GAME_INFO.C
	// static int	get_image_size(t_mapInfo *mi);
	// static mlx_image_t	*make_color_image(t_gameInfo *gi, int size, uint32_t color);
void		free_game_info(t_gameInfo *gi);
t_gameInfo	*init_game_info(char *argv[]);

//HOOKS.C
void		closeme(void	*game_info);
void		key_hooker(mlx_key_data_t keydata, void	*game_info);

// PLAYER_FUNCS.C
	// static t_player	*player_setup(t_gameInfo *gi, char *dir_c, int x, int y)
t_player	*get_player(t_gameInfo *gi);

//PLAYER_MOVEMENT
	// static void	update_player(t_gameInfo *gi, int x, int y);
	// static int	change_x_y(int x, int y, t_gameInfo *gi);
char	coors_in_map(t_gameInfo *gi, int x, int y);
void		player_rotate(t_gameInfo *gi, int orientation);
void		player_move(t_gameInfo *gi, int direction);

//MAIN
void	print_screen (t_gameInfo *game_info);
#endif
