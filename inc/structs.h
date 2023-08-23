/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:59:13 by aumarin           #+#    #+#             */
/*   Updated: 2023/08/23 00:37:10 by aumarin          ###   ########.fr       */
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

#endif