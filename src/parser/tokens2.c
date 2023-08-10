/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:14:55 by aumarin           #+#    #+#             */
/*   Updated: 2023/06/07 18:58:13 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tkobj	*tokens_quotes(char *str_line, t_tokens *tokens, int *idx)
{
	char	*matching_quote;
	char	quote_type;
	long	matching_quote_idx;
	t_tkobj	*result;

	result = malloc(sizeof(t_tkobj) * 1);
	if (!result)
		return (NULL);
	if (tokens[*idx] == QUOTE)
		quote_type = '\'';
	else
		quote_type = '"';
	matching_quote = ft_strchr(str_line + *idx + 1, quote_type);
	if (matching_quote)
		matching_quote_idx = matching_quote - str_line;
	else
		return (NULL);
	//add expand if double_quote
	*idx = matching_quote_idx;
	result->str = ft_strndup(str_line + *idx + 1, \
		matching_quote_idx - *idx - 1);
	result->id = QUOTE;
	return (result);
}

char	*tokens_str(char *str_line, t_tokens *tokens, int *idx)
{
	char	*str;
	char	*tmp;
	t_tkobj	*result;

	result = malloc(sizeof(t_tkobj) * 1);
	if (!result)
		return (NULL);
	str = NULL;
	tmp = ft_calloc(2, sizeof(char));
	if (!tmp)
		return (NULL);
	while (tokens[*idx] && tokens[*idx] == CHAR)
	{
		tmp[0] = str_line[*idx];
		str = ft_strjoin(str, tmp);
		(*idx)++;
	}
	(*idx)--;
	result->str = str;
	result->id = STR;
	return (result);
}

char	*tokens_env(char *str_line, t_tokens *tokens, int *idx)
{
	int		i;
	char	*str;
	t_tkobj	*result;

	result = malloc(sizeof(t_tkobj) * 1);
	if (!result)
		return (NULL);
	str = NULL;
	i = *idx + 1;
	if (tokens[i] == CHAR)
		str = tokens_str(str_line, tokens, &i);
	*idx = i;
	str = ft_strjoin("$", str);
	result->str = str;
	result->id = ENV;
	return (result);
}

//Modify  the new_line item to put the correct OPERATOR
t_line	*tokens_do(char *str_line, t_tokens *tokens)
{
	int		i;
	void	*str;
	t_line	*word_line;

	i = 0;
	str = NULL;
	word_line = NULL;
	while (tokens[i])
	{
		if (tokens[i] == QUOTE || tokens[i] == DOUBLE_QUOTE)
			str = tokens_quotes(str_line, tokens, &i);
		else if (tokens[i] == CHAR)
			str = tokens_str(str_line, tokens, &i);
		else if (tokens[i] == GREAT || tokens[i] == LESS)
			str = tokens_redirects(str_line, tokens, &i);
		else if (tokens[i] == DOLLAR)
			str = tokens_env(str_line, tokens, &i);
		else if (tokens[i] == PIPE)
			new_line_item(&word_line, PIPE_, NULL);
		else
			new_line_item(&word_line, 1, str);
		if (!str)
			return (NULL);
		i++;
	}
	return (word_line);
}
