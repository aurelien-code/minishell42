/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:51:15 by aumarin           #+#    #+#             */
/*   Updated: 2023/08/11 15:33:08 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_lexer_item(t_lexer **lexer, t_lexer_enum type, char value)
{
	t_lexer	*new_item;
	t_lexer	*first_item;

	if (!(*lexer))
		return ;
	new_item = malloc(sizeof(t_lexer));
	first_item = (*lexer);
	if (!new_item)
		return ;
	new_item->value = value;
	new_item->type = type;
	new_item->next = NULL;
	if (!(*lexer)->next)
		(*lexer)->next = new_item;
	else
	{
		while ((*lexer)->next)
			(*lexer) = (*lexer)->next;
		(*lexer)->next = new_item;
		(*lexer) = first_item;
	}
}

t_lexer	*lexer(char *prompt_line)
{
	int		i;
	t_lexer	*lexer;

	if (!prompt_line)
		return (NULL);
	i = 0;
	lexer = NULL;
	while (prompt_line[i] != '\0')
	{
		if (prompt_line[i] == '\'' || prompt_line[i] == '"')
			add_lexer_item(&lexer, QUOTE, prompt_line[i]);
		else if (prompt_line[i] == '|')
			add_lexer_item(&lexer, PIPE, prompt_line[i]);
		else if (prompt_line[i] == '<' || prompt_line[i] == '>')
			add_lexer_item(&lexer, REDIRECT, prompt_line[i]);
		else if (prompt_line[i] == '$')
			add_lexer_item(&lexer, EXPAND, prompt_line[i]);
		else
			add_lexer_item(&lexer, NORMAL, prompt_line[i]);
		i++;
	}
	return (lexer);
}
