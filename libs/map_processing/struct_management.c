/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:36:57 by nroth             #+#    #+#             */
/*   Updated: 2023/10/06 14:29:16 by ymorozov         ###   ########.fr       */
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
		ft_arrfree((void **) map_info->map);
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

uint32_t	rgb_to_hex(char **rgb_arr)
{
	uint32_t	hex;
	int			counter;

	counter = -1;
	while (rgb_arr[++counter])
	{
		if (ft_atoi(rgb_arr[counter]) < 0
			|| ft_atoi(rgb_arr[counter]) > 255)
			return (0);
	}
	hex = 0;
	hex += ft_atoi(rgb_arr[0]) << 24;
	hex += ft_atoi(rgb_arr[1]) << 16;
	hex += ft_atoi(rgb_arr[2]) << 8;
	hex += 255;
	return (hex);
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
	map_info->ceiling_color = 0;
	map_info->floor_color = 0;
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
		if (!map_info->map || !map_info->ceiling_color || !map_info->floor_color
			|| !map_info->texture_paths[i])
			return (error (NULL, "Values missing in map!"), ERR);
			// return (error (map_info, "Values missing in map!"), ERR);
		fd = open (map_info->texture_paths[i], O_RDONLY);
		if (fd < 0)
			return (error (NULL, "Texture file not found!"), ERR);
			// return (error (map_info, "Texture file not found!"), ERR);
		// close (fd);
	}
	return (OK);
}
