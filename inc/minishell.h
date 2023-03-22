/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:32:31 by aumarin           #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD:minishell.h
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2023/03/01 14:56:46 by ypages           ###   ########.fr       */
=======
/*   Updated: 2023/03/07 13:55:02 by aumarin          ###   ########.fr       */
>>>>>>> ff43190 (add: lexer)
=======
/*   Updated: 2023/03/20 12:37:57 by aumarin          ###   ########.fr       */
>>>>>>> f4841c6 (save 12/03/22: start main parser part)
=======
/*   Updated: 2023/03/21 14:07:19 by aumarin          ###   ########.fr       */
>>>>>>> 1c17cd7 (refactor header files + littles advances on parser):inc/minishell.h
=======
/*   Updated: 2023/03/21 20:44:06 by aumarin          ###   ########.fr       */
>>>>>>> 6c7085a (fix: parser segfault)
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
t_env	*check_env_path(char **envp);

/*	exec.c	*/
int		ft_exec(t_env *env);

/*	parser.c	*/
t_line		*parse(char *str_line, t_tokens	*tokens);

/*	line.c		*/
t_line		*new_line_item(t_line **head, t_operators type, char *value);

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
<<<<<<< HEAD
>>>>>>> ff43190 (add: lexer)
=======
void		print_line(t_line *line);
>>>>>>> 6c7085a (fix: parser segfault)

#endif
