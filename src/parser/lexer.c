/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:51:15 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/06 15:50:13 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*substr_lexer(t_lexer *lexer_arr, int start, int stop)
{
	char	*str;
	int		i;

	if (!lexer_arr || stop - start < 1)
		return (NULL);
	i = 0;
	str = ft_calloc(stop - start, sizeof(char *));
	if (!str)
		return (NULL);
	while (i < stop - start - 1)
	{
		str[i] = lexer_arr[start + i + 1].value;
		i++;
	}
	return (str);
}

t_lexer_enum	lex_quotes(char prompt_char, int *in_quote, char *qt_type)
{
	if (!(*qt_type) || (*qt_type) == prompt_char)
	{
		*qt_type = prompt_char;
		*in_quote = !(*in_quote);
		return (QUOTE);
	}
	else
		return (NORMAL);
}

t_lexer_enum	get_type(int i, int in_quote, char *prompt_line)
{
	if (prompt_line[i] == '|' && !in_quote)
		return (PIPE);
	else if ((prompt_line[i] == '<' || prompt_line[i] == '>') && !in_quote)
		return (REDIRECT);
	else
		return (NORMAL);
}

t_lexer	*lexer(char *prompt_line)
{
	int		i;
	t_lexer	*lexer;
	int		in_quote;
	char	quote_type;

	i = 0;
	if (!prompt_line)
		return (NULL);
	lexer = ft_calloc(ft_strlen(prompt_line) + 2, sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	in_quote = 0;
	quote_type = '\0';
	while (prompt_line[i] != '\0')
	{
		if (prompt_line[i] == '\'' || prompt_line[i] == '"')
			lexer[i].type = lex_quotes(prompt_line[i], &in_quote, &quote_type);
		else
			lexer[i].type = get_type(i, in_quote, prompt_line);
		lexer[i].value = prompt_line[i];
		i++;
	}
	return (lexer);
}
