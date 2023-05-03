/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:31:43 by ypages            #+#    #+#             */
/*   Updated: 2023/04/29 15:37:55 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include "../libft/libft.h"
# include "./errors.h"
# include "./enums.h"

/*  DEFINE STRINGS */
# ifndef PROMPT_NAME
#  define PROMPT_NAME "minishell> "
# endif

# ifndef NOK
#  define NOK 0
# endif

# ifndef OK
#  define OK 1
# endif

typedef struct s_line
{
	t_operators		type;
	char			*value;
	struct s_line	*next;
}	t_line;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

/*	builtin	*/
char		*ft_cd(char *path);
void		ft_echo(char *str, int arg);
char		*ft_pwd(void);
t_env		*ft_export(t_env *env, char *var);
t_env		*ft_unset(t_env **env, char *var);
void		ft_env(t_env *env);
/** builtin - utils **/
int			search_var(t_env *env, char *var);

/*	parser.c	*/
t_line		*parse(char *str_line, t_tokens	*tokens);

/*	parser_utils.	*/
int			parser_triple_redirects(t_tokens *tokens, int idx, int do_print);
void		convert_str_builtin(t_line **line);

/*	line.c		*/
t_line		*new_line_item(t_line **head, t_operators type, char *value);

/*  prompt.c    */
char		*ft_prompt(void);

/*	DEBUG	*/
void		print_operator(t_operators op);
void		print_env(char **envp);
void		print_var(char **envp, char *var);

/*	lexer.c		*/
t_tokens	*lexer(char *str);

/*	expand.c	*/
t_line		*expand_env_var(t_line **line);

/*	DEBUG		*/
void		print_operator(t_operators op);
void		print_tokens(t_tokens *tk);
void		print_line(t_line *line);

/*	exec.c		*/
t_env		*ft_exec(t_line *line, t_env *env);

/*	ll_env.c	*/
t_env		*convert_env(char **envp);
t_env		*add_item(t_env *env, char *name, char *value);
t_env		*modify_item(t_env *env, char *name, char *value);
t_env		*delete_item(t_env **env, char *name);

#endif
