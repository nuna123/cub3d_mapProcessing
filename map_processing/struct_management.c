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

/*
	frees the t_mapInfo struct
*/
void	map_info_free(t_mapInfo *map_info)
{
	int	i;

	if (map_info == NULL)
		return ;
	if (map_info->ceiling_rgb)
		free(map_info->ceiling_rgb);
	if (map_info->floor_rgb)
		free(map_info->floor_rgb);
	if (map_info->texture_paths)
	{
		i = -1;
		while (++i < 4)
		{
			if (map_info->texture_paths[i])
				map_info->texture_paths[i] = (free(map_info->texture_paths[i]),
						NULL);
		}
		free (map_info->texture_paths);
	}
	if (map_info->map)
	{
		printf("HERE\n");
		ft_arrfree((void **) map_info->map);
	}
	free (map_info);
}

/*
	frees MapInfo struct, prints a given [Error_msg]
	as well as "Error\n" as defined in the instructions
*/
int	error(t_mapInfo *map_info, char *error_msg)
{
	map_info_free(map_info);
	printf ("Error\n");
	printf("%s\n", error_msg);
	return (ERR);
}

/*
	inits the t_rgb struct to all -1
*/
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

/*
	inits the t_mapInfo struct to all nulls
*/
t_mapInfo	*map_info_init(void)
{
	t_mapInfo	*map_info;
	int			i;

	map_info = malloc (sizeof (t_mapInfo));
	if (!map_info)
		error (NULL, "Memory Allocation Failed!");
	map_info->map_height = 0;
	map_info->map_width = 0;
	map_info->map = NULL;
	map_info->ceiling_rgb = NULL;
	map_info->floor_rgb = NULL;
	map_info->texture_paths = malloc (sizeof (char *) * 5);
	i = -1;
	while (++i < 5)
		map_info->texture_paths[i] = NULL;
	return (map_info);
}

/*
	Final check of t_mapInfo
	checks that all texture paths are present and valid.
	checks that both ceiling rgb and floor rgb are full

*/
int	check_map_info(t_mapInfo *map_info)
{
	int	i;
	int	fd;

	i = -1;
	while (++i < 4)
	{
		if (!map_info->ceiling_rgb || !map_info->floor_rgb
			|| !map_info->texture_paths[i])
			return (error (map_info, "Values missing in map!"), ERR);
		fd = open (map_info->texture_paths[i], O_RDONLY);
		if (fd < 0)
			return (error (map_info, "Texture file not found!"), ERR);
		close (fd);
	}
	return (OK);
}
