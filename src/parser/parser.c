/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:59:35 by aumarin           #+#    #+#             */
/*   Updated: 2023/05/17 13:11:01 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse_command(t_tokens **tokens);

t_ast	*parse_pipe(t_tokens **tokens);

t_ast	*parse_redirect_in(t_tokens **tokens);

t_ast	*parse_redirect_out(t_tokens **tokens);

t_ast	*parse(t_tokens **tokens)
{
	t_ast	*ast;

	ast = parse_pipe(tokens);
	return (ast);
}
