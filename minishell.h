/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:32:31 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/07 13:55:02 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "./libft/libft.h"

/*  DEFINE STRINGS */
# ifndef PROMPT_NAME
#  define PROMPT_NAME "minishell> "
# endif

typedef enum e_tokens
{
	LESS = 1,
	GREAT = 2,
	PIPE = 3,
	QUOTE = 4,
	DOUBLE_QUOTE = 5,
	DOLLAR = 6,
	SPC = 7,
	CHAR = 8
}	t_tokens;

typedef enum e_builtins
{
	ECHO = 1,
	CD = 2,
	PWD = 3,
	EXPORT = 4,
	UNSET = 5,
	ENV = 6,
	EXIT = 7
}	t_builtins;

typedef enum e_operators
{
	SINGLE_L_REDIRECT = 1,
	SINGLE_R_REDIRECT = 2,
	DOUBLE_L_REDIRECT = 3,
	DOUBLE_R_REDIRECT = 4,
	ENV_VAR = 5,
	PIPE_ = 6,
	STR = 7,
	FILE_ = 8,
	BUILTIN = 9
}	t_operators;

typedef struct s_line
{
	t_operators		type;
	char			*value;
	struct s_line	*prev;
	struct s_line	*next;
}	t_line;

/*	parser.c	*/

/*	line.c		*/

/*  prompt.c    */
char		*ft_prompt(void);

/*	lexer.c		*/
t_tokens	*lexer(char *str);

/*	DEBUG		*/
void		print_operator(t_operators op);
void		print_tokens(t_tokens *tk);

#endif