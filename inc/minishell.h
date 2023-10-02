/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:31:43 by ypages            #+#    #+#             */
/*   Updated: 2023/10/02 18:51:25 by aagathe          ###   ########.fr       */
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
# include <sys/wait.h>
# include "../libft/libft.h"
# include "./strings.h"
# include "./enums.h"
# include "./structs.h"

/*	builtin	*/
int			ft_cd(t_cmd *cmds, char *env[]);
int			ft_echo(t_cmd *cmds);
int			ft_pwd(t_cmd *cmds);
int			ft_export(t_cmd *cmds, char ***env);
int			ft_unset(t_cmd *cmds, char ***env);
int			ft_env(t_cmd *cmds, char *env[]);
int			ft_exit(t_cmd *cmds, char **env, int fork);

/** builtin - utils **/
int			get_env_size(char **env);
void		ft_free_split(char **list);
void		ft_free_cpy_env(char **cpy_env);

/*  prompt.c    */
char		*ft_prompt(void);

/*	ll_env.c	*/
t_env		*convert_env(char **envp);
t_env		*add_item(t_env *env, char *name, char *value);
t_env		*modify_item(t_env *env, char *name, char *value);
t_env		*delete_item(t_env **env, char *name);

/*	sig.c		*/
void		sig_setup(int mod);

/*  lexer.c     */
t_lexer		*lexer(char *prompt_line);
char		*substr_lexer(t_lexer *lexer_arr, int start, int stop);

/*	quotes.c	*/
t_tokens	*get_quote_token(t_lexer *lexer_arr, int *i, char **env);

/*	tokens.c	*/
t_tokens	*get_tokens(t_lexer *lexer_arr, char **env);
t_tokens	*new_token_item(char *str, t_tokens_enum type);

/*	expand.c	*/
t_tokens	*expand(t_lexer *lexer_arr, int *i, char **env);
char		*ft_getenv(char **env, char *var);

/*	redirects.c	*/
t_tokens	*get_redirect_token(t_lexer *lexer_arr, int *i);
t_tokens	*handle_redirection(t_cmd *cmd, t_tokens *tokens);
/*	free_memory.c */
void		free_tokens(t_tokens *tokens);

/*	history.c	*/
int			write_history(const char *input);

t_cmd		*parser(t_tokens *tokens);

/* execute.c*/
int			executer(t_cmd *cmds, char **env[]);

/* manage_files */
int			open_pipe(int pfd[4], int nb_cmds, t_cmd *next);
void		close_files(t_cmd *cmds, int pfd[4], int nb_cmds);
void		unswitch_files(t_cmd *cmds, int action);
void		switch_files(t_cmd *cmds, int id_cmd, int pfd[4]);

/* open_files.c */
int			open_files(t_cmd *cmds);

/* pipe_utils.c */
t_cmd		*go_to_cmds(t_cmd *cmds, int nb_cmds);
char		*check_path(char *cmd, char **pathes);
char		**find_pathes(char *env[]);
int			try_fork(void);
void		free_pathes(char **pathes);

void		*throw_parsing_error(t_lexer *lex, t_tokens *tok, \
			t_cmd *cmd, char *err);

int			history_size(int should_increment);
void		free_commands(t_cmd *commands);
void		dbg_print_tokens(t_tokens *tokens);

#endif
