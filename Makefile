COMPILER = cc
FLAGS = -Wall -Wextra -Werror -g 
NAME = minishell
SRCS = minishell.c builtins1.c builtins2.c expansion.c expansion2.c signals.c expansion3.c exit_status.c exit.c builtins_execution.c env_vars_builtins.c env_vars_builtins2.c env_vars_builtins3.c env_vars_builtins4.c env_vars.c undefined_class.c free_functions.c parsing.c execution_functions.c execution_functions2.c tokenization.c redirections.c hfuncs.c
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
