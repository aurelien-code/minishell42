# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/07 22:33:15 by aumarin           #+#    #+#              #
#    Updated: 2023/02/17 12:38:41 by aumarin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
SRC		= 	minishell.c \

OBJ		=	$(SRC:.c=.o)
C_FLAGS	=	-Wall -Wextra -Werror 
CC		=	cc

all: $(NAME)

.c.o:
	@echo "\033[0;33mcompiling... \033[0;37m"
	@$(CC) -o $@ -c $< $(C_FLAGS) -I .

$(NAME): $(OBJ)
	@echo "\033[0;33mlinking... \033[0;37m"	
	@$(CC)  $(C_FLAGS) -o $@ $^

action:
	@$(CC)  $(C_FLAGS) -o $@ $^
	@$(CC) -o $@ -c $< $(C_FLAGS) -I .

clean:
	@echo "\033[0;33mdeleting objects... \033[0;37m"
	@rm -f $(OBJ)
	@echo "\033[0;33mdone \033[0;37m"

fclean: clean
	@rm -f $(OBJ)
	@rm -f $(NAME)

re: fclean all