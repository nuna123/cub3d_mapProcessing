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
# define GAME_H

# include <stdio.h>
# include <math.h>
# include <limits.h>

# include "libft.h"
# include "mapProcessing.h"
# include "MLX42.h"

# define WIDTH 1600
# define HEIGHT 864

# define TEXTURE_SIZE 32

# define FOV 60.0

// MINIMAP VALUES
# define MINIMAP_WIDTH_FACTOR .2		// multiplied by gi->screen_w
# define BCKG_COLOR 0xFF			// black
# define WALL_COLOR 0xFFFFFFFF	// white
# define PLAYER_COLOR 0xFF0FF0FF	// red

//	int	x;  top left corner's x position
//	int	y; top left corner's y position
//	int	angle;  where is it facing
typedef struct s_player
{
	int	x;
	int	y;
	int	angle;
}	t_player;

//TEXTURE ORDER:  E N W S
typedef struct s_gameInfo
{
	mlx_t			*mlx;
	t_mapInfo		*map_info;

	mlx_texture_t	**textures;
	mlx_image_t		*screen_image;
	t_player		*player;
	int				txtr_size;
	int				player_size;

	int				screen_w;
	int				screen_h;

	int				offset; // viewpnt offset
}	t_gameInfo;

// GAME_INFO
void		free_game_info(t_gameInfo *gi);
t_gameInfo	*init_game_info(char *argv[]);

//HOOKS
void		closeme(void *game_info);
void		key_hooker(mlx_key_data_t keydata, void *game_info);
void		our_mousefunc(mouse_key_t button, action_t action, modifier_key_t mods, void* game_info);

// PLAYER_FUNCS
t_player	*get_player(t_gameInfo *gi);

//PLAYER_MOVEMENT
void		player_rotate(t_gameInfo *gi, int orientation);
void		move_player(t_gameInfo *gi, int direction);

//GET_DIST
double		get_dist(t_gameInfo *gi, double angle, int *txtr);

//UTILS
double		dtr(double deg);
void		my_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y,
				uint32_t color);
char		coors_in_map(t_gameInfo *gi, int x, int y);
void		define_texture(double horizontal_dis, double vertical_dis,
				double angle, int *txtr);
uint32_t	get(uint8_t *texture_pixels);

//MINIMAP
void		draw_minimap(t_gameInfo	*gi, mlx_image_t *img, int pos[2]);

//PRINTING
void		line(mlx_image_t *img, double a[2], double b[2], uint32_t color);
mlx_image_t	*print_bcg(t_gameInfo	*gi);
void		print_texture(t_gameInfo *gi, mlx_image_t *img, int vals[3],
				int t_idx);
mlx_image_t	*create_screen_image(t_gameInfo	*gi);
void		print_screen(t_gameInfo *game_info);

#endif
