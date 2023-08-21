NAME		=	new_game
SRC			=	*.c

LIBS_FOL	=	map_processing/ Libft/ MLX42/
LIBS		=	${LIBS_FOL:/=/*.a}


CC			=	cc -ldl -lglfw -pthread -lm -fsanitize=address -g


all: ${NAME}

MLX42/%.a:
	cmake MLX42 -B MLX42
	make -C MLX42

Libft/%.a :
	make -C Libft

map_processing/%.a :
	make -C map_processing

${NAME}: ${SRC} ${LIBS}
	${CC} ${SRC} ${LIBS} -o ${NAME}


clean:
	rm -rf ${NAME}

re: clean all