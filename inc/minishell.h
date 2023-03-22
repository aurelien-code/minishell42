/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:12:50 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/22 20:35:39 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "./errors.h"
# include "./enums.h"

/*  DEFINE STRINGS */
# ifndef PROMPT_NAME
#  define PROMPT_NAME "minishell> "
#  define NOK -1
#  define OK 0
# endif

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
t_env		*check_env_path(char **envp);

/*	exec.c	*/
int			ft_exec(t_env *env);

/*	parser.c	*/
t_line		*parse(char *str_line, t_tokens	*tokens);

/*	line.c		*/
t_line		*new_line_item(t_line **head, t_operators type, char *value);

/*  prompt.c    */
char		*ft_prompt(void);

/*	DEBUG	*/
void		print_operator(t_operators op);
void		print_env(char **envp);

/*	lexer.c		*/
t_tokens	*lexer(char *str);

/*	DEBUG		*/
void		print_operator(t_operators op);
void		print_tokens(t_tokens *tk);
void		print_line(t_line *line);

#endif
