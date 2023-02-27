/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:32:31 by aumarin           #+#    #+#             */
/*   Updated: 2023/02/27 12:23:36 by ypages           ###   ########.fr       */
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
#  define NOK -1
#  define OK 0
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

typedef struct s_env
{
	char			*name;
	char			**value;
	struct s_line	*prev;
	struct s_line	*next;
}	t_env;

/*	environment	*/
int		check_env_path(char **argv, char **envp);

/*	exec.c	*/
int		ft_exec(int argc, char **argv, char **envp);

/*	parser.c	*/
void	parse_line(t_line *line);

/*	line.c	*/
t_line	*get_first(t_line *line);
t_line	*create_line(char *str);

/*  prompt.c    */
t_line	*ft_prompt(void);

/*	DEBUG	*/
void	print_operator(t_operators op);
void	print_env(char **envp);

#endif
