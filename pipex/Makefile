COMPILER = cc
FLAGS = -Wall -Wextra -Werror 
NAME = pipex
SRCS = pipex.c hfuncs.c
OBJS = ${SRCS:.c=.o}

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	@${CC} ${FLAGS} ${OBJS} -L../libft -lft -o ${NAME}

all: ${NAME}


bonus: re

clean:
	@rm -rf ${OBJS}

fclean: clean
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
