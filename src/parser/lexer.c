/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:20:15 by aumarin           #+#    #+#             */
/*   Updated: 2023/05/24 19:07:43 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	char_to_token(char c)
{
	if (c == '<')
		return (LESS);
	else if (c == '>')
		return (GREAT);
	else if (c == '|')
		return (PIPE);
	else if (c == '\'')
		return (QUOTE);
	else if (c == '"')
		return (DOUBLE_QUOTE);
	else if (c == '$')
		return (DOLLAR);
	else if (c == ' ')
		return (SPC);
	else
		return (CHAR);
}

t_tokens	*lexer(char *str)
{
	t_tokens	*tokens;
	int			i;

	i = 0;
	tokens = ft_calloc(ft_strlen(str) + 2, sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	while (str[i])
	{
		tokens[i] = char_to_token(str[i]);
		i++;
	}
	return (tokens);
}
