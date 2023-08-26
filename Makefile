# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/07 22:33:15 by aumarin           #+#    #+#              #
#    Updated: 2023/08/26 13:37:44 by aumarin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

MSRC	=	minishell.c	# main
MOBJ	=	$(MSRC:.c=.o)

SRC		= 	src/prompt.c \
			src/ll_env.c \
			src/sig.c \
			src/free_memory.c \
			src/built/cd.c \
			src/built/echo.c \
			src/built/pwd.c \
			src/built/export.c \
			src/built/unset.c \
			src/built/utils.c \
			src/built/env.c \
			src/parser/lexer.c \
			src/parser/tokens.c \
			src/parser/quotes.c \
			src/parser/expand.c \
			src/parser/redirects.c

OBJ		=	$(SRC:.c=.o)


C_FLAGS	=	-Wall -Wextra -Werror -g3
RD_FLAG = -lreadline
CC		=	cc

LIBFT_DIR = ./libft/


all: $(NAME)

.c.o:
	@echo "\033[0;33mcompiling $< \033[0;37m"
	@$(CC) -o $@ -c $< $(C_FLAGS) -I ./inc/

$(NAME): $(MOBJ) $(OBJ)
	@echo "\033[0;33mlinking $@... \033[0;37m"	
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
