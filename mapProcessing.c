#include "mapProcessing.h"
#include "Libft/libft.h"

#include <stdio.h>
#include <fcntl.h>

void	mapInfo_free(mapInfo_t *mapInfo)
{
	if (!mapInfo)
		return;
	if (mapInfo->ceiling_rgb)
		free(mapInfo->ceiling_rgb);
	if (mapInfo->floor_rgb)
		free(mapInfo->floor_rgb);


	if(mapInfo->texture_paths)
	{
		if (mapInfo->texture_paths[NO])
			free(mapInfo->texture_paths[NO]);
		if (mapInfo->texture_paths[SO])
			free(mapInfo->texture_paths[SO]);
		if (mapInfo->texture_paths[WE])
			free(mapInfo->texture_paths[WE]);
		if (mapInfo->texture_paths[EA])
			free(mapInfo->texture_paths[EA]);
		free (mapInfo->texture_paths);
	}
/* 	if (mapInfo->EA_texture_path)
		free(mapInfo->EA_texture_path);
	if (mapInfo->WE_texture_path)
		free(mapInfo->WE_texture_path);
	if (mapInfo->NO_texture_path)
		free(mapInfo->NO_texture_path);
	if (mapInfo->SO_texture_path)
		free(mapInfo->SO_texture_path); */

	free (mapInfo);
}

void	error (mapInfo_t *mapInfo, char *error_msg)
{
	mapInfo_free(mapInfo);
	printf ("Error\n");
	printf("%s\n", error_msg);
	exit (1);
}

rgb_t *rgb_init(void)
{
	rgb_t	*rgb;
	rgb = malloc (sizeof(rgb_t));
	if (!rgb)
		return (NULL);
	rgb->red = -1;
	rgb->green = -1;
	rgb->blue = -1;

	return (rgb);
}

mapInfo_t *mapInfo_init(void)
{
	mapInfo_t	*mapInfo;
	int			i;

	mapInfo = malloc (sizeof (mapInfo_t));
	if (!mapInfo)
		error (NULL, "Memory Allocation Failed!");

	mapInfo->ceiling_rgb = NULL;
	mapInfo->floor_rgb = NULL;

	mapInfo->texture_paths = malloc (sizeof (char *) * 5);
	i = -1;
	while (++i < 5)
		mapInfo->texture_paths[i] = NULL;


/* 	mapInfo->NO_texture_path = NULL;
	mapInfo->SO_texture_path = NULL;
	mapInfo->WE_texture_path = NULL;
	mapInfo->EA_texture_path = NULL; */

	return (mapInfo);
}


void	textureline_fill(mapInfo_t	*mapInfo, char **mapline_split)
{
	char	*compass_str;
	char	**compass_arr;
	int		i;

	compass_str = ft_strdup("NO|SO|WE|EA");
	compass_arr = ft_split(compass_str,'|');
	i = -1;

	while (++i < 4)
	{
		if (ft_strncmp(compass_arr[i], mapline_split[0], 3) == 0)
		{
			if (!mapInfo->texture_paths[i])
				mapInfo->texture_paths[i] = ft_strtrim(mapline_split[1], "\n");
			else
			{
				free (compass_str);
				ft_arrfree((void **) compass_arr);
				ft_arrfree((void **) mapline_split);
				error(mapInfo, "multiple map texture entries!");
			}
		}
	}
	free (compass_str);
	ft_arrfree((void **) compass_arr);
}

void	rgb_fill(mapInfo_t	*mapInfo, char **mapline_split)
{
	printf("RAGB FILL\n");
	rgb_t	*rgb;
	char	**rgb_arr;

	if ((mapline_split[0][0] == 'F' && !mapInfo->floor_rgb))
		mapInfo->floor_rgb = rgb_init();
	else if(mapline_split[0][0] == 'C' && !mapInfo->ceiling_rgb)
		mapInfo->ceiling_rgb = rgb_init();
	else
		error ((ft_arrfree((void **) mapline_split), mapInfo),
			"Duplicate F/C lines!");
	rgb = mapInfo->ceiling_rgb;
	if (mapline_split[0][0] == 'F')
		rgb = mapInfo->floor_rgb;

	rgb_arr = ft_split(mapline_split[1], ',');

	if (ft_arrlen((void **)rgb_arr) != 3)
	{
		ft_arrfree((void **) mapline_split);
		ft_arrfree((void **) rgb_arr);
		free (rgb);
		error (mapInfo, "Invalid F/C line!");
	}
	rgb->red = ft_atoi(rgb_arr[0]);
	rgb->green = ft_atoi(rgb_arr[1]);
	rgb->blue= ft_atoi(rgb_arr[2]);

	if (rgb->red < 0 || rgb->red > 255 ||
		rgb->green < 0 || rgb->green > 255 ||
		rgb->blue < 0 || rgb->blue > 255)
	{
		ft_arrfree((void **) mapline_split);
		ft_arrfree((void **) rgb_arr);
		free (rgb);
		error (mapInfo, "Invalid F/C line!");
	}
	ft_arrfree((void **) rgb_arr);
}
/*
void	rgb_fill(mapInfo_t	*mapInfo, char **mapline_split)
{
	rgb_t	*rgb;
	char	**rgb_arr;

	if ((mapline_split[0][0] == 'F' && mapInfo->floor_rgb)
	|| (mapline_split[0][0] == 'C' && mapInfo->ceiling_rgb))
		error ((ft_arrfree((void **) mapline_split), mapInfo),
			"Duplicate F/C lines!");

	rgb = rgb_init();
	rgb_arr = ft_split(mapline_split[1], ',');

	if (ft_arrlen((void **)rgb_arr) != 3)
	{
		ft_arrfree((void **) mapline_split);
		ft_arrfree((void **) rgb_arr);
		free (rgb);
		error (mapInfo, "Invalid F/C line!");
	}
	rgb->red = ft_atoi(rgb_arr[0]);
	rgb->green = ft_atoi(rgb_arr[1]);
	rgb->blue= ft_atoi(rgb_arr[2]);

	if (rgb->red < 0 || rgb->red > 255 ||
		rgb->green < 0 || rgb->green > 255 ||
		rgb->blue < 0 || rgb->blue > 255)
	{
		ft_arrfree((void **) mapline_split);
		ft_arrfree((void **) rgb_arr);
		free (rgb);
		error (mapInfo, "Invalid F/C line!");
	}
	if (mapline_split[0][0] == 'F')
		mapInfo->floor_rgb = rgb;
	else
		mapInfo->ceiling_rgb = rgb;
}

 */
void get_info(mapInfo_t	*mapInfo, char *map_line)
{
	printf("GETINFO\n");
	char	**mapline_split;

	mapline_split = ft_split(map_line, ' ');
	if (!mapline_split)
		error (mapInfo, "Error with spitting mapline!");
	if (ft_arrlen((void **) mapline_split) != 2)
		error ((ft_arrfree((void **) mapline_split), mapInfo),
			"Invalid mapline!");

	if (ft_strlen(mapline_split[0]) == 2
		&&	!ft_strchr(mapline_split[0], '|')
		&&	ft_strnstr("NO|SO|WE|EA", mapline_split[0], 11))
		textureline_fill(mapInfo, mapline_split);
	else if (ft_strlen(mapline_split[0]) == 1
		&& (mapline_split[0][0] == 'F' || mapline_split[0][0] == 'C'))
		rgb_fill(mapInfo, mapline_split);
	else
		error ((ft_arrfree((void **) mapline_split), mapInfo),
		"Invalid mapline!");

	ft_arrfree((void **) mapline_split);
}


int	mapInfo_fill(mapInfo_t	*mapInfo, int map_fd)
{
	char	*map_line;

	map_line = get_next_line(map_fd);
	while (map_line)
	{
		if (ft_strncmp(map_line, "\n", 2))
		{
			if (!mapInfo->texture_paths[0] || !mapInfo->texture_paths[1]
				|| !mapInfo->texture_paths[2] || !mapInfo->texture_paths[3]
				|| !mapInfo->ceiling_rgb|| !mapInfo->floor_rgb)
				get_info(mapInfo, map_line);
		}
		free(map_line);
		map_line = get_next_line(map_fd);
	}
	return 0;
}



int main (int argc, char **argv)
{
	char		*map_path = "./map.cub";
	int			map_fd;
	mapInfo_t	*mapInfo;

	if (argc > 1)
		map_path = argv[1];


	//Check map extension
	if (ft_strncmp(&(map_path[ft_strlen(map_path) - ft_strlen(".cub")])
			, ".cub", ft_strlen(".cub")) != 0)
		error(NULL, "Map is not of type .cub!");

	//check that file exists
	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		error(NULL, "Map path is invalid!");

	//init mapInfo, fill
	mapInfo = mapInfo_init();
	if (!mapInfo)
		error((close(map_fd), NULL), "Map initialization failed!");
	mapInfo_fill(mapInfo, map_fd);
	printf ("MAP: \n");
	printf ("rgb: ceiling(%i,%i,%i) floor(%i,%i,%i)\n", mapInfo->ceiling_rgb->red, mapInfo->ceiling_rgb->green, mapInfo->ceiling_rgb->blue , mapInfo->floor_rgb->red, mapInfo->floor_rgb->green, mapInfo->floor_rgb->blue );

	printf("textures: \n\t NO: %s \n\tSO: %s  \n\tWE: %s  \n\tEA: %s\n", mapInfo->texture_paths[0], mapInfo->texture_paths[1], mapInfo->texture_paths[2], mapInfo->texture_paths[3]);

	mapInfo_free(mapInfo);


	close (map_fd);
	return 0;
}