/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:08:01 by aumarin           #+#    #+#             */
/*   Updated: 2023/08/23 12:48:21 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote_closed(t_lexer *lexer_arr, int i)
{
	char	quote;

	if (lexer_arr[i].type == QUOTE)
			quote = lexer_arr[i].value;
	else
		return (0);
	while (lexer_arr[i].value)
	{
		i++;
		if (lexer_arr[i].value == quote)
			return (1);
	}
	return (0);
}

t_tokens	*get_quote_tokens(t_lexer *lexer_arr, int *i)
{
	int			j;
	char		*str;

	j = *i;
	if (!lexer_arr || lexer_arr[*i].type != QUOTE)
		return (NULL);
	if (!is_quote_closed(lexer_arr, *i))
	{
		lexer_arr[*i].type = NORMAL;
		return (NULL);
	}
	while (lexer_arr[j].value)
	{
		j++;
		if (lexer_arr[j].value == lexer_arr[*i].value)
		{
			str = substr_lexer(lexer_arr, *i, j);
			(*i) = j;
			return (new_token_item(str, TOKEN));
		}
	}
	return (NULL);
}
