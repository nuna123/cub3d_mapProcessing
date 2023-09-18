NAME		=	new_game
SRC			=	*.c



MLX_PATH	= ./MLX42/
MLX_BUILD_PATH	= ${addprefix ${MLX_PATH}, build/}
MLX_LIB	= ${addprefix ${MLX_BUILD_PATH}, libmlx42.a}

LIBS_FOL	=	map_processing/ Libft/
LIBS		=	${LIBS_FOL:/=/*.a} ${MLX_LIB}

CC			=	cc -ldl -lglfw -pthread -lm -fsanitize=address -g

###################################################################
GREEN='\033[32m'
NONE='\033[0m'
###################################################################


all: ${NAME}
	@	echo ${GREEN}${NAME}" CREATED!!" ${NONE} ;

${MLX_LIB}:
	cmake ${MLX_PATH} -B ${MLX_BUILD_PATH}
	make -C ${MLX_BUILD_PATH} -s

Libft/%.a :
	make -C Libft -s

map_processing/%.a :
	make -C map_processing -s

${NAME}: ${SRC} ${LIBS} ${MLX_LIB}
	${CC} ${SRC} ${LIBS} -o ${NAME}


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