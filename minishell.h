/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:32:31 by aumarin           #+#    #+#             */
/*   Updated: 2023/02/21 18:23:14 by aumarin          ###   ########.fr       */
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

typedef enum e_operators
{
	SINGLE_L_REDIRECT,
	SINGLE_R_REDIRECT,
	DOUBLE_L_REDIRECT,
	DOUBLE_R_REDIRECT,
	PIPE,
	ENV_VAR,
	OTHER,
	ERROR
}	t_operators;

typedef struct s_line
{
	char			c;
	struct s_line	*prev;
	struct s_line	*next;
}	t_line;

/*	parser.c	*/
void	parse_line(t_line *line);

/*	line.c	*/
t_line	*get_first(t_line *line);
t_line	*create_line(char *str);

/*  prompt.c    */
t_line	*ft_prompt(void);

/*	DEBUG	*/
void	print_operator(t_operators op);

#endif