/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:08:01 by aumarin           #+#    #+#             */
/*   Updated: 2023/09/30 16:35:43 by aumarin          ###   ########.fr       */
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

char	*process_new_str(char *base_str, char *old_str, int i, int j)
{
	char	*tmp[2];
	char	*new_str;

	new_str = NULL;
	tmp[0] = new_str;
	tmp[1] = ft_substr(base_str, i, j);
	if (j != 1)
		new_str = ft_strjoin(old_str, getenv(tmp[1]));
	else
		new_str = ft_strjoin(old_str, tmp[1]);
	if (tmp[0])
		free(tmp[0]);
	if (tmp[1])
		free(tmp[1]);
	if (old_str)
		free(old_str);
	return (new_str);
}

char	*expand_in_double_quote(char **env, char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	new_str = NULL;
	while (str[i])
	{
		j = 1;
		if (str[i] == '$')
		{
			while (str[i + j] != ' ' && str[i + j] && str[i + j] != '$')
				j++;
			new_str = ft_getenv(env, ft_substr(str, i + 1, j));
			i += j;
		}
		if (str[i] != '$')
		{
			new_str = process_new_str(str, new_str, i, 1);
			i++;
		}
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
		lexer_arr[*i].type = NORMAL;
		(*i)--;
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
