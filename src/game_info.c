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
	int	i;

	if (gi->player)
		free(gi->player);
	if (gi->map_info)
		map_info_free(gi->map_info);
	if (gi->textures)
	{
		i = -1;
		while (++i < 4)
		{
			if (gi->textures[i])
				mlx_delete_texture(gi->textures[i]);
		}
		free(gi->textures);
	}
	if (gi->screen_image)
		mlx_delete_image(gi->mlx, gi->screen_image);
	mlx_terminate(gi->mlx);
	free(gi);
}
	/* gi->E_texture = mlx_load_png(gi->map_info->texture_paths[0]);
	if (!gi->E_texture)
		return (ERR);

	gi->N_texture = mlx_load_png(gi->map_info->texture_paths[1]);
	if (!gi->N_texture)
		return (ERR);

	gi->W_texture = mlx_load_png(gi->map_info->texture_paths[2]);
	if (!gi->W_texture)
		return (ERR);

	gi->S_texture = mlx_load_png(gi->map_info->texture_paths[3]);
	if (!gi->S_texture)
		return (ERR); */
int	gi_create_textures(t_gameInfo *gi)
{
	gi->textures = ft_calloc (sizeof(mlx_texture_t	*), 5);
	gi->textures[0] = mlx_load_png(gi->map_info->texture_paths[0]);
	if (!gi->textures[0])
		return (ERR);
	gi->textures[1] = mlx_load_png(gi->map_info->texture_paths[1]);
	if (!gi->textures[1])
		return (ERR);
	gi->textures[2] = mlx_load_png(gi->map_info->texture_paths[2]);
	if (!gi->textures[2])
		return (ERR);
	gi->textures[3] = mlx_load_png(gi->map_info->texture_paths[3]);
	if (!gi->textures[3])
		return (ERR);

	gi->screen_image = mlx_new_image(gi->mlx,
			gi->texture_size * gi->map_info->map_width,
			gi->texture_size * gi->map_info->map_height);
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
	gi->mlx = mlx_init(WIDTH, HEIGHT, "Our Awesome Game", false);
	if (!gi->mlx)
		return (map_info_free(gi->map_info), free(gi), NULL);
	gi->texture_size = TEXTURE_SIZE;
	gi->player_size = TEXTURE_SIZE / 2;
	gi->player = get_player(gi);
	if (!gi->player)
		return (map_info_free(gi->map_info), free(gi), NULL);
	if (gi_create_textures(gi) == ERR)
		return (free_game_info(gi), NULL);
	gi->screen_w = WIDTH;
	gi->screen_h = HEIGHT;
	return (gi);
}
