# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 11:17:28 by barbizu-          #+#    #+#              #
#    Updated: 2022/06/07 16:14:35 by barbizu-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = pipex.c pipex_utils.c

OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

${NAME}: libft
		${CC} ${CFLAGS} ${SRCS} -L ./libft -lft -o ${NAME}

all:	${NAME}

libft:
	make -C ./libft

clean:
		${RM} -f ${OBJS}
		make clean -C ./libft

fclean:	clean
		make fclean -C ./libft
		${RM} -f ${NAME}

re:		fclean ${MAKE} ${NAME}

.PHONY: all clean fclean re libft
