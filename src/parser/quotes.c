/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:08:01 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/06 07:03:51 by aumarin          ###   ########.fr       */
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
	int			j;
	char		*str;
	char		*tmp2;
	char		*tmp;
	int			x;

	j = *i;
	if (!lexer_arr || lexer_arr[*i].type != QUOTE)
		return (NULL);

	while (lexer_arr[j].value)
	{
		tmp2 = NULL;
		j++;
		if (lexer_arr[j].value == lexer_arr[*i].value)
		{
			if (lexer_arr[j + 1].value == lexer_arr[*i].value)
			{
				lexer_arr[j].value = ' ';
				lexer_arr[j + 1].value = '\b';
				j++;
				continue ;
			}
			else if (lexer_arr[j + 1].value != ' ' && \
				lexer_arr[j + 1].value != '\t' && (lexer_arr[j + 1].type == NORMAL || lexer_arr[j+1].type == NORMAL))
			{
				tmp = substr_lexer(lexer_arr, *i, j);
				x = j;
				j++;
				while (lexer_arr[j].value && lexer_arr[j].type == NORMAL)
					j++;
				tmp2 = substr_lexer(lexer_arr, x, j);
			}
			if (tmp2 && tmp)
			{
				str = ft_strjoin(tmp, tmp2);
				free(tmp);
				free(tmp2);
			}
			else
				str = substr_lexer(lexer_arr, *i, j);
			if (lexer_arr[j].type == QUOTE)
				{/*ICI
				IL
				FAUT
				FAIRE
				UN TRUC*/ continue ;}
			(*i) = j - 1;
			return (new_token_item(str, TOKEN));
		}
	}
	return (NULL);
}
