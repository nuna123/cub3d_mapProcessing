
NAME = map_processing.a

SRCS = map_processing.c	struct_management.c	valueProcessing.c

OBJ_FOL = ./objs/
OBJS = ${addprefix ${OBJ_FOL}, ${SRCS:.c=.o}}

CC_FLGS = -Wall -Wextra -Werror
CC = cc ${CC_FLGS}

####################################################################
####################################################################
NRM_COLOR = \033[0;39m

GREEN = \033[0;92m
YELLOW = \033[0;93m
####################################################################
####################################################################

all:${NAME}

${OBJ_FOL}%.o : %.c
	@ mkdir -p ${OBJ_FOL}
	@ ${CC} -c $^ -o $@

${NAME}: ${OBJS}
	ar -crs ${NAME} ${OBJS}
	@ echo "${GREEN}${NAME} created!${NRM_COLOR}"

clean:
	rm -rf ${OBJ_FOL}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: re fclean clean all