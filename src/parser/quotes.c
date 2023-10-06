/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:08:01 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/06 11:44:23 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

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

t_tokens	*get_quote_token(t_lexer *lexer_arr, int *i)
{
	int		j;
	int		k;
	char	*str;
	char	*tmp;

	if (!lexer_arr || lexer_arr[*i].type != QUOTE)
		return (NULL);
	j = *i + 1;
	str = NULL;
	tmp = NULL;
	while (lexer_arr[j].value)
	{
		if (lexer_arr[j].type != QUOTE && lexer_arr[j].type == NORMAL)
		{
			k = j;
			while (lexer_arr[j].value && lexer_arr[j].value != lexer_arr[*i].value && \
				lexer_arr[j].value != ' ' && lexer_arr[j].value != '\t' && lexer_arr[j].type == NORMAL)
				j++;
			tmp = substr_lexer(lexer_arr, k - 1, j);
			if (!str && tmp && ft_strlen(tmp) > 0)
				str = tmp;
			else if (ft_strlen(tmp) == 0)
				break ;
			else
				str = ft_strjoin(str, tmp);
		}
		else if ((lexer_arr[j].type == QUOTE || lexer_arr[j].type == NORMAL) && \
				lexer_arr[j].value != ' ' && lexer_arr[j].value != '\t' && lexer_arr[j+1].type)
		{
			j++;
			continue;
		}
		else
		{
			(*i) = j - 1;
			//printf("str(1): %s\n", str);
			return (new_token_item(str, TOKEN));
		}
	}
	if (str)
	{
			(*i) = j - 1;
			//printf("str(2): %s\n", str);
			return (new_token_item(str, TOKEN));
	}
	return (NULL);
}
