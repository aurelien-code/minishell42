/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:59:13 by aumarin           #+#    #+#             */
/*   Updated: 2023/05/22 15:13:21 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			*value;
}	t_ast;

#endif