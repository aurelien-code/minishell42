/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:32:31 by aumarin           #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2023/03/01 14:56:46 by ypages           ###   ########.fr       */
=======
/*   Updated: 2023/03/07 13:55:02 by aumarin          ###   ########.fr       */
>>>>>>> ff43190 (add: lexer)
=======
/*   Updated: 2023/03/20 12:37:57 by aumarin          ###   ########.fr       */
>>>>>>> f4841c6 (save 12/03/22: start main parser part)
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
	struct s_line	*next;
}	t_line;

typedef struct s_env
{
	char			**content;
	int				status;
	struct s_env	*next;
}	t_env;

/*	environment	*/
t_env	*check_env_path(char **envp);

/*	exec.c	*/
int		ft_exec(t_env *env);

/*	parser.c	*/
t_line		*parse(char *str_line, t_tokens	*tokens);

/*	line.c		*/

/*  prompt.c    */
char		*ft_prompt(void);

<<<<<<< HEAD
/*	DEBUG	*/
void	print_operator(t_operators op);
void	print_env(char **envp);
void	print_list(t_env *list);
=======
/*	lexer.c		*/
t_tokens	*lexer(char *str);

/*	DEBUG		*/
void		print_operator(t_operators op);
void		print_tokens(t_tokens *tk);
>>>>>>> ff43190 (add: lexer)

#endif
