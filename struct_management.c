/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:36:57 by nroth             #+#    #+#             */
/*   Updated: 2023/08/01 13:36:58 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mapProcessing.h"

void	map_info_free(t_mapInfo *map_info)
{
	int	i;

	if (!map_info)
		return ;
	if (map_info->ceiling_rgb)
		free(map_info->ceiling_rgb);
	if (map_info->floor_rgb)
		free(map_info->floor_rgb);
	if (map_info->texture_paths)
	{
		i = -1;
		while (++i < 4)
			if (map_info->texture_paths[i])
				free(map_info->texture_paths[i]);
		free (map_info->texture_paths);
	}
	if (map_info->map)
	{
		i = -1;
		while (map_info->map[++i])
			free(map_info->map[i]);
		free (map_info->map);
	}
	free (map_info);
}

int	error(t_mapInfo *map_info, char *error_msg)
{
	map_info_free(map_info);
	printf ("Error\n");
	printf("%s\n", error_msg);
	return (ERR);
}

t_rgb	*rgb_init(void)
{
	t_rgb	*rgb;

	rgb = malloc (sizeof(t_rgb));
	if (!rgb)
		return (NULL);
	rgb->red = -1;
	rgb->green = -1;
	rgb->blue = -1;
	return (rgb);
}

t_mapInfo	*map_info_init(void)
{
	t_mapInfo	*map_info;
	int			i;

	map_info = malloc (sizeof (t_mapInfo));
	if (!map_info)
		error (NULL, "Memory Allocation Failed!");
	map_info->map = NULL;
	map_info->ceiling_rgb = NULL;
	map_info->floor_rgb = NULL;
	map_info->texture_paths = malloc (sizeof (char *) * 5);
	i = -1;
	while (++i < 5)
		map_info->texture_paths[i] = NULL;
	return (map_info);
}
