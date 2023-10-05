/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:59:13 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/05 23:54:49 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "./enums.h"

typedef struct s_lexer
{
	t_lexer_enum		type;
	char				value;
}	t_lexer;

typedef struct s_tokens
{
	char			*value;
	t_tokens_enum	type;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redr
{
	t_tokens_enum	type;
	char			*filename;
	int				fd;
	int				pfd[2];
	int				direction;
	struct s_redr	*next;
}	t_redr;

typedef struct s_cmd
{
	char			**cmd;
	char			*res;
	int				is_builtin;
	int				old_stdin;
	int				old_stdout;
	int				pid;
	struct s_redr	*redr;
	//struct s_redr	*redr_in;
	//struct s_redr	*redr_out;
	struct s_cmd	*next;
}	t_cmd;

#endif
