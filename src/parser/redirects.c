/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:17:04 by aumarin           #+#    #+#             */
/*   Updated: 2023/08/26 02:09:14 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*handle_double_redirect(t_lexer *lexer_arr, int *i, int j)
{
	t_tokens	*token;

	if (lexer_arr[*i].value != lexer_arr[*i + 1].value)
	{
		(*i) = j - 1;
		return (NULL);
	}
	if (lexer_arr[*i].value == '<')
		token = (new_token_item(NULL, D_REDIR_L));
	else
		token = (new_token_item(NULL, D_REDIR_R));
	(*i) = j - 1;
	return (token);
}

t_tokens	*handle_single_redirect(t_lexer *lexer_arr, int *i)
{
	if (lexer_arr[*i].value == '<')
		return (new_token_item(NULL, S_REDIR_L));
	else
		return (new_token_item(NULL, S_REDIR_R));
}

t_tokens	*get_redirect_token(t_lexer *lexer_arr, int *i)
{
	int			redir_size;
	int			j;

	j = *i;
	redir_size = 0;
	while (lexer_arr[j].type == REDIRECT)
	{
		redir_size++;
		j++;
	}
	if (redir_size > 2)
	{
		(*i) = j - 1;
		printf("Too many redirection symbols\n");
		return (NULL);
	}
	else if (redir_size == 2)
		return (handle_double_redirect(lexer_arr, i, j));
	else
		return (handle_single_redirect(lexer_arr, i));
	return (NULL);
}
