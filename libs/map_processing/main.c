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

int	main(int argc, char **argv)
{
	char		*map_path;
	t_mapInfo	*map_info;

	map_path = "./map_mapproc.cub";
	map_info = NULL;
	if (argc > 1)
		map_path = argv[1];
	map_info = get_map(map_path);
	if (!map_info)
		return (1);
	for(int i = 0; map_info->map[i];i++)
	{
		printf("%s\n",  map_info->map[i]);
	}
	map_info_free(map_info);
	return (0);
}
