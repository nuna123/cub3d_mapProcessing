NAME		=	cub3d



SRC_FOL	=	./src/
SRC			=	${addprefix ${SRC_FOL}, *.c}

INCLD = ./include/

MLX_PATH	= ./libs/MLX42/
LIBFT_PATH	= ./libs/Libft/
MAP_PROC_PATH	= ./libs/map_processing/

MLX_BUILD_PATH	= ${addprefix ${MLX_PATH}, build/}
MLX_LIB	= ${addprefix ${MLX_BUILD_PATH}, libmlx42.a}

LIBS_FOL	=	${MAP_PROC_PATH} ${LIBFT_PATH}
LIBS		=	${LIBS_FOL:/=/*.a} ${MLX_LIB}

CC			=	cc -ldl -lglfw -pthread -g -lm -Wall -Werror -Wextra -fsanitize=address

###################################################################
GREEN='\033[32m'
NONE='\033[0m'
###################################################################


all: ${NAME}
	@	echo ${GREEN}${NAME}" CREATED!!" ${NONE} ;

${MLX_LIB}:
	cmake ${MLX_PATH} -B ${MLX_BUILD_PATH}
	make -C ${MLX_BUILD_PATH} -s

${LIBFT_PATH}%.a :
	make -C ${LIBFT_PATH} -s

${MAP_PROC_PATH}%.a :
	make -C ${MAP_PROC_PATH} -s

${NAME}: ${SRC} ${LIBS} ${INCLD}* ${MLX_LIB}
	${CC} ${SRC} ${LIBS} -I${INCLD} -o ${NAME}


fclean:
		rm -rf ${NAME}
		rm -rf ${MLX_BUILD_PATH}
	@	echo  ${GREEN} ${MLX_BUILD_PATH} " deleted!\n" ${NONE}

	@	for LIB in ${LIBS_FOL}; do \
			make -C $$LIB fclean ; echo ${GREEN} $$LIB " deleted!\n" ${NONE} ;\
		done

clean:
	@	for LIB in ${LIBS_FOL} ${MLX_BUILD_PATH}; do \
			make -C $$LIB clean; echo ${GREEN} $$LIB " deleted!\n" ${NONE}; \
		done

re: fclean all