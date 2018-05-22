##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## navy
##

NAME		=	a.out

CC		=	cc

CFLAGS		+=	-g3 -Wall -W -Wextra -Iinclude/

LDFLAGS		=	-lsfml-network -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lcsfml-network -lcsfml-graphics -lcsfml-audio -lcsfml-window -lcsfml-system

SRCS_PREFIX	=	src/

FILES		=

MAIN		=	$(addprefix $(SRCS_PREFIX), main.c)

SRCS		=	$(addprefix $(SRCS_PREFIX), $(FILES))

OBJ		=	$(SRCS:.c=.o) $(MAIN:.c=.o)

all:			$(NAME)

.PHONY: fclean clean all re tests_run

RED	=\033[0;31m
GREEN	=\033[0;32m
NC	=\033[0m
GREY	=\033[90m
BG_COLOR= \033[46m####\033[m



$(NAME):	$(OBJ)
	@echo -e '${BG_COLOR}Flags: $(CFLAGS)${NC}'
	@echo -e '${RED}Create${NC}: ${GREY}./$(NAME)${NC}'
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o:		%.c
	@echo -e '${GREEN} [ OK ]${NC} Build $<'
	@$(CC) $(LDFLAGS) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_T)
	@rm -rf vgcore.*
	@rm -f gmon.out
	@rm -rf a.out
	@find . -name *.gc* -delete
	@echo -e '${RED}Clean${NC} : OK'

fclean:		clean
	@rm -rf $(NAME)
	@echo -e '${RED}Fclean${NC}: ./$(NAME) removed'

re:		fclean all
