/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valueProcessing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:08:32 by nroth             #+#    #+#             */
/*   Updated: 2023/10/06 13:09:38 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapProcessing.h"

/* gets called when a line defining a texture file path is found in the file. */
int	textureline_fill(t_mapInfo	*map_info, char **mapline_split)
{
	char	*compass_str;
	char	**compass_arr;
	int		i;

	compass_str = ft_strdup("EA|NO|WE|SO");
	compass_arr = ft_split(compass_str, '|');
	i = -1;
	while (++i < 4)
	{
		if (ft_strncmp(compass_arr[i], mapline_split[0], 3) == 0)
		{
			if (!map_info->texture_paths[i])
				map_info->texture_paths[i] = ft_strtrim(mapline_split[1], "\n");
			else
			{
				free (compass_str);
				ft_arrfree((void **) compass_arr);
				ft_arrfree((void **) mapline_split);
				return (error(map_info, "multiple map texture entries!"));
			}
		}
	}
	free (compass_str);
	ft_arrfree((void **) compass_arr);
	return (OK);
}

/*
	gets called when a line defining a rgb for
	floor/ceiling is found in the file.
*/
int	rgb_fill(t_mapInfo	*map_info, char **mapline_split)
{
	uint32_t	color;
	char		**rgb_arr;

	rgb_arr = ft_split(mapline_split[1], ',');
	if (ft_arrlen((void **)rgb_arr) != 3)
		return (ft_arrfree((void **) mapline_split),
			ft_arrfree((void **) rgb_arr),
			error (map_info, "Invalid F/C line!"));
	color = rgb_to_hex(rgb_arr);
	if (!color)
		return (ft_arrfree((void **) mapline_split),
			ft_arrfree((void **) rgb_arr),
			error (map_info, "Invalid F/C line!"));
	if ((mapline_split[0][0] == 'F' && !map_info->floor_color))
		map_info->floor_color = color;
	else if (mapline_split[0][0] == 'C' && !map_info->ceiling_color)
		map_info->ceiling_color = color;
	else
		return (error ((ft_arrfree((void **) mapline_split),
					map_info), "Duplicate F/C lines!"));
	return (ft_arrfree((void **) rgb_arr), OK);
}

/*calls rgb_fill() or textureline_fill()*/
int	get_info(t_mapInfo	*map_info, char *map_line)
{
	char	**mapline_split;

	mapline_split = ft_split(map_line, ' ');
	if (!mapline_split)
		return (error (map_info, "Error with splitting mapline!"));
	if (ft_arrlen((void **) mapline_split) != 2)
		return (error ((ft_arrfree((void **) mapline_split), map_info),
				"Invalid mapline!"));
	if (ft_strlen(mapline_split[0]) == 2
		&& !ft_strchr(mapline_split[0], '|')
		&& ft_strnstr("NO|SO|WE|EA", mapline_split[0], 11))
	{
		if (textureline_fill(map_info, mapline_split) == ERR)
			return (ERR);
	}
	else if (ft_strlen(mapline_split[0]) == 1
		&& (mapline_split[0][0] == 'F' || mapline_split[0][0] == 'C'))
	{
		if (rgb_fill(map_info, mapline_split) == ERR)
			return (ERR);
	}
	else
		return (error ((ft_arrfree((void **) mapline_split), map_info),
				"Invalid mapline!"));
	return (ft_arrfree((void **) mapline_split), OK);
}

/* processes the map array or the info fields in the map_nfo struct */
int	map_info_fill(t_mapInfo	*map_info, int map_fd)
{
	char	*map_line;

	map_line = get_next_line(map_fd);
	while (map_line)
	{
		if (ft_strncmp(map_line, "\n", 2))
		{
			if (is_map_line(map_line) == OK)
			{
				if (process_map_arr(map_line, map_info, map_fd) == ERR)
					return (ERR);
				map_line = ft_strdup(":)");
			}
			else if (get_info(map_info, map_line) == ERR)
			{
				while (map_line)
					map_line = (free(map_line), get_next_line(map_fd));
				return (free (map_line), ERR);
			}
		}
		map_line = (free(map_line), get_next_line(map_fd));
	}
	return (check_map_info(map_info));
}

//The actual main function called.
t_mapInfo	*get_map(char *map_path)
{
	int			map_fd;
	t_mapInfo	*map_info;

	if (ft_strncmp(&(map_path[ft_strlen(map_path) - ft_strlen(".cub")])
			, ".cub", ft_strlen(".cub")) != 0)
		return (error(NULL, "Map is not of type .cub!"), NULL);
	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		return (error(NULL, "Map path is invalid!"), NULL);
	map_info = map_info_init();
	if (!map_info || map_info_fill(map_info, map_fd) == ERR)
	{
		if (map_info)
			map_info_free(map_info);
		return (close (map_fd), printf("Map initialization failed!\n"), NULL);
	}
	return (close (map_fd), map_info);
}
