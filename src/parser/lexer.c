/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:51:15 by aumarin           #+#    #+#             */
/*   Updated: 2023/08/11 16:17:56 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lexer(char *prompt_line)
{
	int		i;
	t_lexer	*lexer;

	if (!prompt_line)
		return (NULL);
	i = 0;
	lexer = ft_calloc(ft_strlen(prompt_line), sizeof(t_lexer));
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
