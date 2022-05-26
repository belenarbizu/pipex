NAME = pipex

SRCS = pipex.c

OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

.c.o:
	${CC} ${CFLAGS} -g -c $< -I libft -o ${<:.c=.o}

${NAME}: ${OBJS}
		@make -C libft
		@cp libft/libft.a ${NAME}
		ar -rc ${NAME} ${OBJS}

all:	${NAME}

clean:
		${RM} ${OBJS}
		@make -sC ./libft/ clean

fclean:
		${RM} ${NAME}

re:		fclean ${MAKE} ${NAME}

.PHONY: all clean fclean re
