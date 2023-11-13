/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:08:32 by nroth             #+#    #+#             */
/*   Updated: 2023/10/06 13:03:26 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapProcessing.h"

//Functions to fill the actual map layout and check its validity
int	is_map_line(char *map_line)
{
	while (*map_line && *map_line != '\n')
	{
		if (!ft_isdigit(*map_line) && *map_line != ' ')
			return (ERR);
		map_line++;
	}
	return (OK);
}

static int	isvalid_firstline(char *line)
{
	if (!line)
		return (ERR);
	while (*line)
	{
		if (*line != '1' && *line != ' ')
			return (ERR);
		if (*line == ' ')
			*line = '1';
		line++;
	}
	return (OK);
}

static int	isvalid_midline(char *line)
{
	while (line && *line == ' ')
		*(line++) = '1';
	if (!line || *line != '1')
		return (ERR);
	while (*line)
	{
		if (!line[1] && *line != '1')
			return (ERR);
		else if (!ft_strchr(ALLOWED_MAPCHARS, *line))
			return (ERR);
		line++;
	}
	return (OK);
}

static int	isvalid_map(char **map, int map_width)
{
	int		i;
	int		player_found;
	char	*temp_line;

	i = 0;
	player_found = 0;
	if (isvalid_firstline(map[i--]) == ERR)
		return (ERR);
	while (map[++i])
	{
		while ((int)ft_strlen (map[i]) < map_width)
		{
			temp_line = ft_strjoin(map[i], "1");
			free(map[i]);
			map[i] = temp_line;
		}
		if (isvalid_midline(map[i]) == ERR)
			return (ERR);
		if (ft_strchr(map[i], 'N') || ft_strchr(map[i], 'S')
			|| ft_strchr(map[i], 'E') || ft_strchr(map[i], 'W'))
			player_found++;
	}
	if (isvalid_firstline(map[i - 1]) == ERR || player_found != 1)
		return (ERR);
	return (OK);
}

int	process_map_arr(char *map_line, t_mapInfo *map_info, int map_fd)
{
	char	**map;
	int		i;

	map = ft_calloc(sizeof(char *), 1);
	map[0] = NULL;
	while (map_line)
	{
		i = -1;
		while (map_line[++i])
			if (map_line[i] == 'C')
				map_info->star_count ++;
		map = ft_arrappend (map, ft_strtrim(map_line, "\n"));
		map_info->map_height ++;
		if ((int) ft_strlen (map_line) - 1 > map_info->map_width)
			map_info->map_width = ft_strlen (map_line) - 1;
		map_line = (free (map_line), get_next_line(map_fd));
	}
	if (isvalid_map(map, map_info->map_width) == ERR)
	{
		ft_arrfree((void **) map);
		return (error (NULL, "Invalid Map!\n"), ERR);
	}
	map_info->map = map;
	return (OK);
}
