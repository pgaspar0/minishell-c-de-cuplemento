SRCS = util ft_printf util2 
SRC = $(addsuffix .c, ${SRCS})
OBJS = $(SRC:.c=.o)
NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar rc
RM = rm -f
RA = ranlib
VERDE = \033[1;32m
VERMELHO = \033[5;31m
AZUL = \033[1;34m
RESTAURA = \033[0m

all: ${NAME}
	@echo "${VERDE}Compilação concluída com sucesso!${RESTAURA}"

${NAME}: ${OBJS}
	@${AR} ${NAME} ${OBJS}
	@${RA} ${NAME}
	@echo "${AZUL}Biblioteca ${NAME} criada com sucesso!${RESTAURA}"

.o.c: 
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.0}
	@echo "${VERDE}Arquivo $< compilado com sucesso!${RESTAURA}"

clean:
	@${RM} ${OBJS} ${teste_obj}
	@echo "${VERMELHO}Objectos eliminados!${RESTAURA}"

fclean: clean
	@${RM} ${NAME} 
	@echo "${VERMELHO}Objectos e ${NAME} eliminados!${RESTAURA}"

re: fclean all
	@echo "${VERDE}Arquivos recompilados com sucesso!${RESTAURA}"

.PHONY: all clean fclean re
