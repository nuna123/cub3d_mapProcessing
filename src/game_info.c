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

void	free_game_info(t_gameInfo *gi)
{
	if (gi->player)
		free(gi->player);
	if (gi->map_info)
		map_info_free(gi->map_info);
	if (gi->bckg_texture)
		mlx_delete_texture(gi->bckg_texture);
	if (gi->player_texture)
		mlx_delete_texture(gi->player_texture);
	if (gi->wall_texture)
		mlx_delete_texture(gi->wall_texture);
	if (gi->screen_image)
		mlx_delete_image(gi->mlx, gi->screen_image);
	mlx_terminate(gi->mlx);
	free(gi);
}

int	gi_create_textures(t_gameInfo *gi)
{
	gi->bckg_texture = mlx_load_png("./textures/white32x32.png");
	if (!gi->bckg_texture)
		return (ERR);
	gi->wall_texture = mlx_load_png("./textures/black32x32.png");
	if (!gi->wall_texture)
		return (ERR);
	gi->player_texture = mlx_load_png("./textures/player16x16.png");
	if (!gi->player_texture)
		return (ERR);
	gi->screen_image = mlx_new_image(gi->mlx,
			TEXTURE_SIZE * gi->map_info->map_width,
			TEXTURE_SIZE * gi->map_info->map_height);
	if (!gi->screen_image)
		return (ERR);
	ft_memset(gi->screen_image->pixels, 255,
		gi->screen_image->width * gi->screen_image->height * 4);
	return (OK);
}

t_gameInfo	*init_game_info(char *argv[])
{
	t_gameInfo	*gi;

	gi = ft_calloc(1, sizeof(t_gameInfo));
	if (!gi)
		return (NULL);
	gi->map_info = get_map(argv[1]);
	if (!gi->map_info)
		return (free(gi), NULL);
	gi->mlx = mlx_init(WIDTH, HEIGHT, "blah", true);
	if (!gi->mlx)
		return (map_info_free(gi->map_info), free(gi), NULL);
	gi->image_size = TEXTURE_SIZE;
	gi->player_size = PLAYER_SIZE;
	gi->player = get_player(gi);
	if (!gi->player)
		return (map_info_free(gi->map_info), free(gi), NULL);
	if (gi_create_textures(gi) == ERR)
		return (free_game_info(gi), NULL);
	return (gi);
}
