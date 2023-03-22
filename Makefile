# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/07 22:33:15 by aumarin           #+#    #+#              #
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#    Updated: 2023/02/21 18:24:05 by aumarin          ###   ########.fr        #
=======
#    Updated: 2023/03/20 14:02:55 by aumarin          ###   ########.fr        #
>>>>>>> f4841c6 (save 12/03/22: start main parser part)
=======
#    Updated: 2023/03/21 10:11:30 by aumarin          ###   ########.fr        #
>>>>>>> 1c17cd7 (refactor header files + littles advances on parser)
=======
#    Updated: 2023/03/22 17:38:56 by ypages           ###   ########.fr        #
>>>>>>> 5ad4186 (env - Finder implement)
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
SRC		= 	minishell.c \
			src/parser.c \
			src/prompt.c \
			src/line.c \
<<<<<<< HEAD
=======
			src/lexer.c \
			env/env.c \
>>>>>>> 5ad4186 (env - Finder implement)
			debug/print_utils.c
OBJ		=	$(SRC:.c=.o)
<<<<<<< HEAD
C_FLAGS	=	-Wall -Wextra -Werror -g3
RD_FLAGS = -lreadline
=======
C_FLAGS	=	-Wall -Wextra -Werror
RD_FLAG = -lreadline
>>>>>>> f4841c6 (save 12/03/22: start main parser part)
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
