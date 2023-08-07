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

int	get_map(char *map_path, t_mapInfo	*map_info)
{
	int	map_fd;

	if (ft_strncmp(&(map_path[ft_strlen(map_path) - ft_strlen(".cub")])
			, ".cub", ft_strlen(".cub")) != 0)
		return (error(NULL, "Map is not of type .cub!"));
	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		return (error(NULL, "Map path is invalid!"));
	map_info = map_info_init();
	if (!map_info)
		return (printf("Map initialization failed!\n"), ERR);
	if (map_info_fill(map_info, map_fd) == ERR)
		return (close (map_fd), printf("Map initialization failed!\n"), ERR);
	map_info_free(map_info);
	return (close (map_fd), OK);
}

int	main(int argc, char **argv)
{
	char		*map_path;
	t_mapInfo	*map_info;

	map_path = "./map.cub";
	map_info = NULL;
	if (argc > 1)
		map_path = argv[1];
	if (get_map(map_path, map_info) != OK)
		return (1);
	map_info_free(map_info);
	return (0);
}
