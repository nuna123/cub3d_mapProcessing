/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:11:15 by nroth             #+#    #+#             */
/*   Updated: 2023/10/18 16:44:45 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <math.h>


#include "libft.h"
#include "mapProcessing.h"
#include "MLX42.h"
#include <limits.h>

#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

#define WIDTH 1600
#define HEIGHT 864

#define TEXTURE_SIZE 32

#define FOV 60.0
#define CAM_DIS 1386


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

	mlx_texture_t	**textures; // E N W S
/* 	mlx_texture_t	*S_texture;
	mlx_texture_t	*E_texture;
	mlx_texture_t	*W_texture; */

	mlx_image_t		*screen_image;
	t_player		*player;
	int				texture_size;
	int				player_size;

	int				screen_w;
	int				screen_h;
} t_gameInfo;

// GAME_INFO.C
	// static int	get_image_size(t_mapInfo *mi);
	// static mlx_image_t	*make_color_image(t_gameInfo *gi, int size, uint32_t color);
void		free_game_info(t_gameInfo *gi);
t_gameInfo	*init_game_info(char *argv[]);

//HOOKS.C
void		closeme(void	*game_info);
void		key_hooker(mlx_key_data_t keydata, void	*game_info);
void		resize_hook(int32_t width, int32_t height, void	*game_info);

// PLAYER_FUNCS.C
	// static t_player	*player_setup(t_gameInfo *gi, char *dir_c, int x, int y)
t_player	*get_player(t_gameInfo *gi);

//PLAYER_MOVEMENT
	// static void	update_player(t_gameInfo *gi, int x, int y);
	// static int	change_x_y(int x, int y, t_gameInfo *gi);
char	coors_in_map(t_gameInfo *gi, int x, int y);
void		player_rotate(t_gameInfo *gi, int orientation);
void		move_player(t_gameInfo *gi, int direction);

//MAIN
void	print_screen (t_gameInfo *game_info);
void	my_put_pixel(mlx_image_t* img, uint32_t x, uint32_t y, uint32_t color);

//GET_DIST .C
double	get_vert_dist(t_gameInfo	*gi, double angle);
double	get_horiz_dist(t_gameInfo	*gi, double angle);
double get_dist (t_gameInfo *gi, double angle, int *txtr, FILE ** fp);

//UTILS
double	dtr(double deg);
void	my_put_pixel(mlx_image_t* img, uint32_t x, uint32_t y, uint32_t color);
char	coors_in_map(t_gameInfo *gi, int x, int y);


void	line(mlx_image_t *img, double a[2], double b[2], uint32_t txtr);
//MINIMAP
void draw_minimap (t_gameInfo	*gi, mlx_image_t *img, int pos[2]);

#endif
