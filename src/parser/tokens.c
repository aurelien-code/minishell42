/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:58:13 by aumarin           #+#    #+#             */
/*   Updated: 2023/08/23 12:48:49 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*new_token_item(char *str, t_tokens_enum type)
{
	t_tokens	*token;

	token = ft_calloc(1, sizeof(t_tokens));
	if (!token)
		return (NULL);
	token->value = str;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	append_token(t_tokens **tokens, t_tokens *new_elem)
{
	if (!(*tokens))
		(*tokens) = new_elem;
	else
	{
		while ((*tokens)->next)
			(*tokens) = (*tokens)->next;
		if (!(*tokens)->next)
			(*tokens)->next = new_elem;
	}
}

void	get_tokens(t_lexer *lexer_arr)
{
	int			i;
	t_tokens	*tokens;

	tokens = NULL;
	i = 0;
	while (lexer_arr[i].value)
	{
		if (lexer_arr[i].type == QUOTE)
			append_token(&tokens, get_quote_tokens(lexer_arr, &i));
		/*
		else if (lexer_arr[i].type == EXPAND)
		else if (lexer_arr[i].type == PIPE)
		else if (lexer_arr[i].type == REDIRECT)
		else
		*/
		i++;
	}
}
