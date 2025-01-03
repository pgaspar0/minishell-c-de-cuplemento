COMPILER = cc
FLAGS = -Wall -Wextra -Werror 
NAME = minishell
SRCS = minishell.c parse.c parse2.c concat.c pipex.c hfuncs.c hfuncs2.c
OBJS = ${SRCS:.c=.o}

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	@make -s -C libft MAKEFLAGS=-silent
	@${CC} ${FLAGS} ${OBJS} -lreadline -L./libft -lft -o ${NAME}

all: ${NAME}


clean:
	@make clean -s -C libft MAKEFLAGS=-silent
	@rm -rf ${OBJS}

fclean: clean
	@make fclean -s -C libft MAKEFLAGS=-silent
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
