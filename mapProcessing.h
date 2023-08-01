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

# define NO 0
# define SO 1
# define WE	2
# define EA	3

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
}	t_mapInfo;

#endif
