# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/07 22:33:15 by aumarin           #+#    #+#              #
#    Updated: 2023/04/27 13:42:08 by aumarin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

MSRC	=	minishell.c	# main
MOBJ	=	$(MSRC:.c=.o)

SRC		= 	src/parser/parser.c \
			src/parser/lexer.c \
			src/parser/parser_utils.c \
			src/prompt.c \
			src/line.c \
			src/expand.c \
			src/exec.c \
			src/ll_env.c \
			src/built/cd.c \
			src/built/echo.c \
			src/built/pwd.c \
			src/built/export.c \
			src/built/unset.c \
			src/built/utils.c \
			src/built/env.c \
			debug/print_utils.c \
			debug/print_env.c
OBJ		=	$(SRC:.c=.o)

TST_SRC =	tests/tst_main.c \
			munit/munit.c \
			tests/tst_parser.c \
			tests/tst_line.c
TST_OBJ =	$(TST_SRC:.c=.o) 

C_FLAGS	=	-Wall -Wextra -Werror -g3
RD_FLAG = -lreadline
CC		=	cc

LIBFT_DIR = ./libft/


all: $(NAME)

.c.o:
	@echo "\033[0;33mcompiling... \033[0;37m"
	@$(CC) -o $@ -c $< $(C_FLAGS) -I ./inc/

$(NAME): $(MOBJ) $(OBJ)
	@echo "\033[0;33mlinking... \033[0;37m"	
	@make -C $(LIBFT_DIR)
	@$(CC)  $(C_FLAGS) -o $@ $^ ./libft/libft.a $(RD_FLAG)

test: $(TST_OBJ) $(OBJ)
	@echo "\033[0;33mlinking... \033[0;37m"	
	@make -C $(LIBFT_DIR)
	@$(CC)  $(C_FLAGS) -o $@ $^ ./libft/libft.a $(RD_FLAG)

clean:
	@echo "\033[0;33mdeleting objects... \033[0;37m"
	@rm -f $(OBJ)
	@rm -f $(MOBJ)
	@rm -f $(TST_OBJ)
	@make clean -C $(LIBFT_DIR)
	@echo "\033[0;33mdone \033[0;37m"

fclean: clean
	@rm -f $(OBJ)
	@rm -f test
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all
