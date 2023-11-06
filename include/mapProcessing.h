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

//TEXTURE ORDER E N W S
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

//VALUE PROCESSING
t_mapInfo	*get_map(char *map_path); //THE ACTUAL MAIN FUNCTION

#endif
