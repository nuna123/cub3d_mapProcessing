/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapProcessing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:08:23 by nroth             #+#    #+#             */
/*   Updated: 2023/08/01 13:08:27 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPPROCESSING_H
# define MAPPROCESSING_H

# define OK 0
# define ERR 1

# define ALLOWED_MAPCHARS "NSEW10 "
# include "libft.h"

# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

typedef struct s_mapInfo
{
	int			map_width;
	int			map_height;

	uint32_t	ceiling_color;
	uint32_t	floor_color;

	char		**texture_paths;

	char		**map;
}	t_mapInfo;

//STRUCT MANAGEMENT
void		map_info_free(t_mapInfo *map_info);
/* int			error(t_mapInfo *map_info, char *error_msg);
t_mapInfo	*map_info_init(void);
int			check_map_info(t_mapInfo *map_info);
uint32_t	rgb_to_hex(char **rgb_arr); */

//VALUE PROCESSING
/* int			textureline_fill(t_mapInfo	*map_info, char **mapline_split);
int			rgb_fill(t_mapInfo	*map_info, char **mapline_split);
int			get_info(t_mapInfo	*map_info, char *map_line);
int			map_info_fill(t_mapInfo	*map_info, int map_fd); */
t_mapInfo	*get_map(char *map_path); //THE ACTUAL MAIN FUNCTION

//MAP PROCESSING
// int			is_map_line(char *map_line);
// int			process_map_arr(char *map_line, t_mapInfo *map_info, int map_fd);
#endif
