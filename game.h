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


#include "./Libft/libft.h"
#include "./map_processing/mapProcessing.h"
#include "./MLX42/include/MLX42/MLX42.h"



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

	mlx_image_t	*bckg_image;
	mlx_image_t	*wall_image;
	mlx_image_t	*player_image;

	t_player	*player;

	int	image_size;


} t_gameInfo;

#endif
