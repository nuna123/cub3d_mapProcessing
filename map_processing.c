/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapProcessing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:08:32 by nroth             #+#    #+#             */
/*   Updated: 2023/08/01 13:08:34 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapProcessing.h"

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

int	isvalid_firstline(char *line)
{
	if (!line)
		return (ERR);
	while (*line)
	{
		if (*line != '1' && *line != ' ')
			return (ERR);
		line++;
	}
	return (OK);
}

int	isvalid_midline(char *line)
{
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

int	isvalid_map(char **map)
{
	int	i;

	i = 0;
	if (isvalid_firstline(map[i]) == ERR)
		return (ERR);
	while (map[++i])
	{
		if (isvalid_midline(map[i]) == ERR)
			return (ERR);
	}
	if (isvalid_firstline(map[i - 1]) == ERR)
		return (ERR);
	return (OK);
}

int	process_map(char *map_line, t_mapInfo *map_info, int map_fd)
{
	char	**map;

	map = ft_calloc(sizeof(char *), 1);
	map[0] = NULL;
	while (map_line)
	{
		map = ft_arrappend (map, ft_strtrim(map_line, "\n"));
		map_line = (free (map_line), get_next_line(map_fd));
	}
	if (isvalid_map(map) == ERR)
	{
		ft_arrfree((void **) map);
		return (error (map_info, "Invalid Map!\n"), ERR);
	}
	map_info->map = map;
	return (OK);
}
