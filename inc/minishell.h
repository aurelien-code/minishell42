/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:31:43 by ypages            #+#    #+#             */
/*   Updated: 2023/08/10 17:22:59 by aumarin          ###   ########.fr       */
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

/*	DEBUG	*/
void		print_env(char **envp);
void		print_var(char **envp, char *var);

/*	expand.c	*/
t_line		*expand_env_var(t_line **line);

/*	DEBUG		*/
void		print_line(t_line *line);
void		print_ast(t_ast *ast);

/*	exec.c		*/
t_env		*ft_exec(t_line *line, t_env *env);

/*	ll_env.c	*/
t_env		*convert_env(char **envp);
t_env		*add_item(t_env *env, char *name, char *value);
t_env		*modify_item(t_env *env, char *name, char *value);
t_env		*delete_item(t_env **env, char *name);

/*	sig.c		*/
void		sig_init(void);
void		sig_ctrl_d(void);

#endif
