/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:17:04 by aumarin           #+#    #+#             */
/*   Updated: 2023/09/16 12:53:25 by aumarin          ###   ########.fr       */
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

int	handle_redirection(t_tokens **tokens, t_redr **redirection, t_cmd **command)
{
	if (!*redirection)
	{
		*redirection = ft_calloc(1, sizeof(t_redr));
		if (!*redirection)
			return (0);
		(*redirection)->fd = -1;
	}
	(*redirection)->type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN)
		return (0);
	(*redirection)->filename = ft_strdup((*tokens)->value);
	if ((*redirection)->type == D_REDIR_L || (*redirection)->type == S_REDIR_L)
	{
		if (!(*command)->redr_in)
			(*command)->redr_in = *redirection;
		else
			return (0);
	}
	else if (!(*command)->redr_out)
		(*command)->redr_out = *redirection;
	else
		return (0);
	return (1);
}