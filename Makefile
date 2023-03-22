# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/07 22:33:15 by aumarin           #+#    #+#              #
#    Updated: 2023/03/22 19:06:35 by aumarin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
SRC		= 	minishell.c \
			src/parser.c \
			src/prompt.c \
			src/line.c \
			src/lexer.c \
			env/env.c \
			debug/print_utils.c
OBJ		=	$(SRC:.c=.o)
C_FLAGS	=	-Wall -Wextra -Werror
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