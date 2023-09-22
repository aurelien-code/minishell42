/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:58:13 by aumarin           #+#    #+#             */
/*   Updated: 2023/09/22 12:24:24 by aumarin          ###   ########.fr       */
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
	t_tokens	*first;

	if (!(*tokens))
		(*tokens) = new_elem;
	else
	{
		first = (*tokens);
		while ((*tokens)->next)
			(*tokens) = (*tokens)->next;
		if (!(*tokens)->next)
			(*tokens)->next = new_elem;
		(*tokens) = first;
	}
}

t_tokens	*get_word_token(t_lexer *lexer_arr, int *i)
{
	char	*str;

	str = NULL;
	while (lexer_arr[*i].type == NORMAL && lexer_arr[*i].value != ' ')
	{
		if (!str && lexer_arr[*i].value)
			str = &lexer_arr[*i].value;
		else
			str = ft_strjoin(str, &lexer_arr[*i].value);

		(*i)++;
	}
	if (lexer_arr[*i].value != ' ')
		(*i)--;
	if (str)
		return (new_token_item(str, TOKEN));
	else
		return (NULL);
}

void	dbg_print_tokens(t_tokens *tokens)
{
	if (!tokens)
		printf("tokens is null\n");
	while (tokens)
	{	
		printf("v = %s | t = %d | n = %p\n", tokens->value, tokens->type,
			tokens->next);
		tokens = tokens->next;
	}
}

t_tokens	*get_tokens(t_lexer *lexer_arr)
{
	int			i;
	t_tokens	*tokens;

	tokens = NULL;
	i = 0;
	if (!lexer_arr)
		return (NULL);
	while (lexer_arr[i].value)
	{
		if (lexer_arr[i].type == QUOTE)
			append_token(&tokens, get_quote_token(lexer_arr, &i));
		else if (lexer_arr[i].type == EXPAND)
			append_token(&tokens, expand(lexer_arr, &i));
		else if (lexer_arr[i].type == PIPE)
			append_token(&tokens, new_token_item(NULL, T_PIPE));
		else if (lexer_arr[i].type == REDIRECT)
			append_token(&tokens, get_redirect_token(lexer_arr, &i));
		else
			append_token(&tokens, get_word_token(lexer_arr, &i));
		i++;
	}
	return (tokens);
}
