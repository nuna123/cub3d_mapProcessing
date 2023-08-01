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

int	main (int argc, char **argv)
{
	char		*map_path = "./map.cub";
	int			map_fd;
	t_mapInfo	*map_info;

	if (argc > 1)
		map_path = argv[1];


	//Check map extension
	if (ft_strncmp(&(map_path[ft_strlen(map_path) - ft_strlen(".cub")])
			, ".cub", ft_strlen(".cub")) != 0)
		return (error(NULL, "Map is not of type .cub!"));

	//check that file exists
	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		return (error(NULL, "Map path is invalid!"));

	//init map_info, fill
	map_info = map_info_init();
	if (!map_info)
		return (printf("Map initialization failed!\n"), ERR);

	if (map_info_fill(map_info, map_fd) == ERR)
		return (close (map_fd), printf("Map initialization failed!\n"), ERR);


	printf ("MAP: \n");
	printf ("rgb: ceiling(%i,%i,%i) floor(%i,%i,%i)\n", map_info->ceiling_rgb->red, map_info->ceiling_rgb->green, map_info->ceiling_rgb->blue , map_info->floor_rgb->red, map_info->floor_rgb->green, map_info->floor_rgb->blue );
	printf("textures: \n\t NO: %s \n\tSO: %s  \n\tWE: %s  \n\tEA: %s\n", map_info->texture_paths[0], map_info->texture_paths[1], map_info->texture_paths[2], map_info->texture_paths[3]);

	printf ("\n");
	for (char **map = map_info->map; *map; map++)
		printf("\t%s\n", *map);


	map_info_free(map_info);

	close (map_fd);
	return 0;
}
