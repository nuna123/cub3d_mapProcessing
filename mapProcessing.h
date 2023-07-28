#ifndef MAPPROCESSING_H
# define MAPPROCESSING_H


# define NO 0
# define SO 1
# define WE	2
# define EA	3


typedef struct rgb_s
{
	int red;
	int green;
	int blue;
} rgb_t;

typedef struct mapInfo_s
{
	rgb_t	*ceiling_rgb;
	rgb_t	*floor_rgb;

	char	**texture_paths;

/* 	char	*NO_texture_path;
	char	*SO_texture_path;
	char	*WE_texture_path;
	char	*EA_texture_path; */
	
} mapInfo_t;


#endif