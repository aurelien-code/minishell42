/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:58:13 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/04 08:36:24 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

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

int	append_token(t_tokens **tokens, t_tokens *new_elem)
{
	t_tokens	*first;

	if (!new_elem)
		return (0);
	if (new_elem->type == 10)
	{
		free_tokens(new_elem);
		return (1);
	}
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
	return (1);
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


t_tokens	*get_tokens(char *str, t_lexer *lexer_arr, char **env)
{
	int			i;
	t_tokens	*tokens;
	int			ret;

	tokens = NULL;
	i = 0;
	ret = 1;
	if (!lexer_arr)
		return (NULL);
	while (i < (int)ft_strlen(str))
	{
		if (lexer_arr[i].type == QUOTE)
			append_token(&tokens, get_quote_token(lexer_arr, &i, env));
		else if (lexer_arr[i].type == EXPAND)
			ret = append_token(&tokens, expand(lexer_arr, &i, env));
		else if (lexer_arr[i].type == PIPE)
			append_token(&tokens, new_token_item(NULL, T_PIPE));
		else if (lexer_arr[i].type == REDIRECT)
			ret = append_token(&tokens, get_redirect_token(lexer_arr, &i));
		else
			ret = append_token(&tokens, get_word_token(lexer_arr, &i, env));
		if (ret == 0)
		{
			free_tokens(tokens);
			return (NULL);
		}
		i++;
	}
	//dbg_print_tokens(tokens);
	return (tokens);
}
