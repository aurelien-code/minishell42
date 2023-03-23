# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/07 22:33:15 by aumarin           #+#    #+#              #
#    Updated: 2023/03/23 04:40:16 by ypages           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
SRC		= 	minishell.c \
			src/parser.c \
			src/prompt.c \
			src/line.c \
			src/lexer.c \
			src/env.c \
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
C_FLAGS	=	-Wall -Wextra -Werror -g3
RD_FLAG = -lreadline
CC		=	cc

LIBFT_DIR = ./libft/


all: $(NAME)

.c.o:
	@echo "\033[0;33mcompiling... \033[0;37m"
	@$(CC) -o $@ -c $< $(C_FLAGS) -I ./inc/

$(NAME): $(OBJ)
	@echo "\033[0;33mlinking... \033[0;37m"	
	@make -C $(LIBFT_DIR)
	@$(CC)  $(C_FLAGS) -o $@ $^ ./libft/libft.a $(RD_FLAG)

clean:
	@echo "\033[0;33mdeleting objects... \033[0;37m"
	@rm -f $(OBJ)
	@make clean -C $(LIBFT_DIR)
	@echo "\033[0;33mdone \033[0;37m"

fclean: clean
	@rm -f $(OBJ)
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all
