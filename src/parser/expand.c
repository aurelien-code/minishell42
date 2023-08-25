/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:43:39 by aumarin           #+#    #+#             */
/*   Updated: 2023/08/25 11:02:04 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

t_tokens	*expand(t_lexer *lexer_arr, int *i)
{
	int			j;
	t_tokens	*token;

	j = 0;
	if (lexer_arr[*i].type != EXPAND)
		return (NULL);
	if (lexer_arr[*i + 1].value == '?')
		return (new_token_item(ft_itoa(g_exit_code), TOKEN));
	while (lexer_arr[*i + j].value && lexer_arr[*i].type == EXPAND)
	{
		j++;
		if (lexer_arr[*i + j].value == ' ' || lexer_arr[*i + j].value == '\0')
		{
			token = new_token_item(getenv(substr_lexer(lexer_arr, *i, *i + j)),
					TOKEN);
			(*i) = j - 1;
			return (token);
		}
	}
	return (NULL);
}
