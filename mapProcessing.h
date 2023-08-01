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
# include "Libft/libft.h"

# include <stdio.h>
# include <fcntl.h>

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

typedef struct s_mapInfo
{
	t_rgb	*ceiling_rgb;
	t_rgb	*floor_rgb;

	char	**texture_paths;

	char	**map;
}	t_mapInfo;

//STRUCT MANAGEMENT
void		map_info_free(t_mapInfo *map_info);
int			error(t_mapInfo *map_info, char *error_msg);
t_rgb		*rgb_init(void);
t_mapInfo	*map_info_init(void);

//VALUE PROCESSING
void		textureline_fill(t_mapInfo	*map_info, char **mapline_split);
int			rgb_fill(t_mapInfo	*map_info, char **mapline_split);
int			get_info(t_mapInfo	*map_info, char *map_line);
int			map_info_fill(t_mapInfo	*map_info, int map_fd);

//MAP PROCESSING
int			is_map_line(char *map_line);
int			process_map(char *map_line, t_mapInfo *map_info, int map_fd);
#endif
