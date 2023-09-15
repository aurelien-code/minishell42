/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:31:43 by ypages            #+#    #+#             */
/*   Updated: 2023/09/06 10:02:44 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include "../libft/libft.h"
# include "./strings.h"
# include "./enums.h"
# include "./structs.h"

/*	builtin	*/
char		*ft_cd(char *path, t_env **env);
void		ft_echo(char *str, int arg);
char		*ft_pwd(void);
t_env		*ft_export(t_env *env, char *var);
t_env		*ft_unset(t_env **env, char *var);
void		ft_env(t_env *env);

/** builtin - utils **/
int			search_var(t_env *env, char *var);

/*  prompt.c    */
char		*ft_prompt(void);

/*	ll_env.c	*/
t_env		*convert_env(char **envp);
t_env		*add_item(t_env *env, char *name, char *value);
t_env		*modify_item(t_env *env, char *name, char *value);
t_env		*delete_item(t_env **env, char *name);

/*	sig.c		*/
void		sig_init(void);
void		sig_ctrl_d(void);

/*  lexer.c     */
t_lexer		*lexer(char *prompt_line);
char		*substr_lexer(t_lexer *lexer_arr, int start, int stop);

/*	quotes.c	*/
t_tokens	*get_quote_token(t_lexer *lexer_arr, int *i);

/*	tokens.c	*/
t_tokens	*get_tokens(t_lexer *lexer_arr);
t_tokens	*new_token_item(char *str, t_tokens_enum type);

/*	expand.c	*/
t_tokens	*expand(t_lexer *lexer_arr, int *i);

/*	redirects.c	*/
t_tokens	*get_redirect_token(t_lexer *lexer_arr, int *i);

/*	free_memory.c */
void		free_tokens(t_tokens *tokens);

/*	history.c	*/
int			write_history(const char *input);


t_cmd		*parser(t_tokens *tokens);

#endif
