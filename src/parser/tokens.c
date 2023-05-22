/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:51:53 by aumarin           #+#    #+#             */
/*   Updated: 2023/05/17 12:54:19 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tokens_str(char *str_line, t_tokens *tokens, int *idx)
{
	char	*str;
	char	*tmp;

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
	return (str);
}

char	*tokens_env(t_line **line, char *str_line, t_tokens *tokens, int *idx)
{
	int		i;
	char	*str;

	str = NULL;
	i = *idx + 1;
	if (tokens[i] == CHAR)
		str = tokens_str(str_line, tokens, &i);
	*idx = i;
	str = ft_strjoin("$", str);
	new_line_item(line, ENV_VAR, str);
	return (str);
}

void	tokens_quotes(t_line **line, char *str_line, t_tokens *tokens, int *idx)
{
	int			tmp;
	t_tokens	quote;
	char		*tmp_str;

	quote = tokens[*idx];
	tmp = *idx + 1;
	while (tokens[tmp] && tokens[tmp] != quote)
	{
		if (tokens[tmp] == DOLLAR && quote == DOUBLE_QUOTE)
		{
			tmp_str = ft_substr(str_line, *idx + 1, tmp - *idx - 1);
			new_line_item(line, STR, tmp_str);
			tokens_env(line, str_line, tokens, &tmp);
			*idx = tmp - 1;
		}
		else
			tmp++;
	}
	if (tokens[tmp] == quote && tmp - 1 - *idx > 0)
		new_line_item(line, STR, ft_substr(str_line, *idx + 1, tmp - 1 - *idx));
	if (tokens[tmp] != quote)
		printf("%s\n", UNCLOSE_QUOTE_ERR);
	*idx = tmp;
}

void	tokens_redirects(t_line **line, t_tokens *tokens, int *idx)
{
	if (parser_triple_redirects(tokens, *idx, 1))
		(*idx) += parser_triple_redirects(tokens, *idx, 0);
	else if (tokens[*idx + 1] == tokens[*idx])
	{
		if (tokens[*idx] == GREAT)
			new_line_item(line, DOUBLE_R_REDIRECT, NULL);
		else if (tokens[*idx] == LESS)
			new_line_item(line, DOUBLE_L_REDIRECT, NULL);
		(*idx)++;
	}
	else
	{
		if (tokens[*idx] == LESS && tokens[*idx + 1] == GREAT)
			printf("%s\n", REDIR_NEWLINE_ERR);
		else if (tokens[*idx] == GREAT && tokens[*idx + 1] == LESS)
			printf("%s\n", REDIR_SYNTAX_ERR);
		else
		{
			if (tokens[*idx] == GREAT)
				new_line_item(line, SINGLE_R_REDIRECT, NULL);
			else
				new_line_item(line, SINGLE_L_REDIRECT, NULL);
		}
	}
}

t_line	*tokens_do(char *str_line, t_tokens	*tokens)
{
	t_line		*line;
	int			i;
	char		*value;

	i = -1;
	line = NULL;
	while (tokens[++i])
	{
		value = NULL;
		if (tokens[i] == QUOTE || tokens[i] == DOUBLE_QUOTE)
			tokens_quotes(&line, str_line, tokens, &i);
		else if (tokens[i] == CHAR)
			value = tokens_str(str_line, tokens, &i);
		else if (tokens[i] == GREAT || tokens[i] == LESS)
			tokens_redirects(&line, tokens, &i);
		else if (tokens[i] == DOLLAR)
			tokens_env(&line, str_line, tokens, &i);
		else if (tokens[i] == PIPE)
			new_line_item(&line, PIPE_, NULL);
		if (value != NULL)
			new_line_item(&line, STR, value);
	}
	convert_str_builtin(&line);
	expand_env_var(&line);
	return (line);
}
