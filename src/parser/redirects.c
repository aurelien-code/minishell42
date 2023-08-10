/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:05:51 by aumarin           #+#    #+#             */
/*   Updated: 2023/06/07 18:17:31 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_double_redirects(t_tokens *tokens, int *idx)
{
	if (tokens[*idx] == GREAT)
		return (t_operators_to_string(DOUBLE_R_REDIRECT));
	else if (tokens[*idx] == LESS)
		return (t_operators_to_string(DOUBLE_L_REDIRECT));
	(*idx)++;
	return (NULL);
}

char	*process_single_redirects(t_tokens *tokens, int *idx)
{
	if (tokens[*idx] == LESS && tokens[*idx + 1] == GREAT)
		printf("%s\n", REDIR_NEWLINE_ERR);
	else if (tokens[*idx] == GREAT && tokens[*idx + 1] == LESS)
		printf("%s\n", REDIR_SYNTAX_ERR);
	else
	{
		if (tokens[*idx] == GREAT)
			return (t_operators_to_string(SINGLE_R_REDIRECT));
		else
			return (t_operators_to_string(SINGLE_L_REDIRECT));
	}
	return (NULL);
}

char	*tokens_redirects(char *str_line, t_tokens *tokens, int *idx)
{
	if (parser_triple_redirects(tokens, *idx, 1))
		(*idx) += parser_triple_redirects(tokens, *idx, 1);
	else if (tokens[*idx + 1] == tokens[*idx])
		return (process_double_redirects(tokens, idx));
	else
		return (process_single_redirects(tokens, idx));
	(void)str_line;
	return (NULL);
}
