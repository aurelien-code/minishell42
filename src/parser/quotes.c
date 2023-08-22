/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:08:01 by aumarin           #+#    #+#             */
/*   Updated: 2023/08/14 17:56:23 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_quote_closed(t_lexer lexer_arr, int idx)
{
	char	quote;

	if (lexer_arr[i].type == QUOTE)
		quote = lexer_arr[i].value;
	else
		return (0);
	while (lexer_arr[i].value)
	{
		if (lexer[i].value == quote)
			return (1);
		i++;
	}
	return (0);
}

t_tokens	*get_quote_tokens(t_lexer lexer_arr, int idx, t_tokens **tokens)
{
	if (!lexer_arr)
		return (NULL);
	
}
