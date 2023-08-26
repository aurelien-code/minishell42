/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:51:15 by aumarin           #+#    #+#             */
/*   Updated: 2023/08/26 13:18:18 by aumarin          ###   ########.fr       */
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

t_lexer	*lexer(char *prompt_line)
{
	int		i;
	t_lexer	*lexer;

	if (!prompt_line || ft_strlen(prompt_line) < 1)
		return (NULL);
	i = 0;
	lexer = ft_calloc(ft_strlen(prompt_line) + 1, sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	while (prompt_line[i] != '\0')
	{
		if (prompt_line[i] == '\'' || prompt_line[i] == '"')
			lexer[i].type = QUOTE;
		else if (prompt_line[i] == '|')
			lexer[i].type = PIPE;
		else if (prompt_line[i] == '<' || prompt_line[i] == '>')
			lexer[i].type = REDIRECT;
		else if (prompt_line[i] == '$')
			lexer[i].type = EXPAND;
		else
			lexer[i].type = NORMAL;
		lexer[i].value = prompt_line[i];
		i++;
	}
	return (lexer);
}
