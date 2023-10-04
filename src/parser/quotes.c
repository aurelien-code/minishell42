/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:08:01 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/04 01:13:06 by aumarin          ###   ########.fr       */
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

char	*expand_in_double_quote(char **env, char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = NULL;
	while (str[i])
	{
		if (str[i] == '$')
			handle_dollar(env, str, &i, &new_str);
		else
			handle_other_char(str, i, &new_str);
		i++;
	}
	free(str);
	return (new_str);
}

t_tokens	*get_quote_token(t_lexer *lexer_arr, int *i, char **env)
{
	int		j;
	char	*str;

	j = *i;
	if (!lexer_arr || lexer_arr[*i].type != QUOTE)
		return (NULL);
	if (!is_quote_closed(lexer_arr, *i))
	{
		g_exit_code = 2;
		ft_putstr_fd(UNCLOSE_QUOTE_ERR, 2);
		return (NULL);
	}
	while (lexer_arr[j].value)
	{
		j++;
		if (lexer_arr[j].value == lexer_arr[*i].value)
		{
			str = substr_lexer(lexer_arr, *i, j);
			if (lexer_arr[*i].value == '"' && ft_strchr(str, '$') && str)
				str = expand_in_double_quote(env, str);
			(*i) = j;
			return (new_token_item(str, TOKEN));
		}
	}
	return (NULL);
}
