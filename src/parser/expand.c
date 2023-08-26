/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:43:39 by aumarin           #+#    #+#             */
/*   Updated: 2023/08/26 15:32:42 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

t_tokens	*expand(t_lexer	*lexer_arr, int	*i)
{
	int		j;
	char	*new_str;
	char	*tmp;
	char	*tmp_sublxr;

	new_str = NULL;
	j = (*i) + 1;
	if (lexer_arr[j].value == '?')
	{
		(*i)++;
		return (new_token_item(ft_itoa(g_exit_code), TOKEN));
	}
	if (lexer_arr[*i].value == '$')
	{
		while (lexer_arr[j].value && lexer_arr[j].value != ' ' && \
			lexer_arr[j].value != '$' && lexer_arr[j].type == NORMAL)
				j++;
		tmp = new_str;
		tmp_sublxr = substr_lexer(lexer_arr, *i, j);
		new_str = ft_strjoin(new_str, getenv(tmp_sublxr));
		free(tmp);
		free(tmp_sublxr);
		*i = j - 1;
	}
	return (new_token_item(new_str, TOKEN));
}
