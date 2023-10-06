/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:08:01 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/06 17:41:41 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	is_quote_closed(t_lexer *lex, int i)
{
	char	quote;

	if (lex[i].type == QUOTE)
			quote = lex[i].value;
	else
		return (0);
	while (lex[i].value)
	{
		i++;
		if (lex[i].value == quote)
			return (1);
	}
	return (0);
}

char	*join_str(char *str, char *tmp)
{
	char	*new_str;

	if (!str && tmp && ft_strlen(tmp) > 0)
		new_str = tmp;
	else
	{
		new_str = ft_strjoin(str, tmp);
		free(tmp);
	}
	return (new_str);
}

void	handle_basic(t_lexer *lex, int *j, int i, char **str)
{
	int		k;
	char	*tmp;
	char	*tmp2;

	k = *j;
	tmp2 = NULL;
	while (lex[*j].value && lex[*j].value != lex[i].value)
	{
		(*j)++;
		if (lex[*j].value == lex[i].value || lex[*j].type != NORMAL)
			break ;
	}
	tmp = substr_lexer(lex, k - 1, *j);
	tmp2 = *str;
	*str = join_str(tmp2, tmp);
	if (tmp2)
		free(tmp2);
}

t_tokens	*get_quote_token(t_lexer *lex, int *i)
{
	int		j;
	char	*str;

	j = *i + 1;
	str = NULL;
	while (lex[j].value)
	{
		if (lex[j].type != QUOTE && lex[j].type == NORMAL)
			handle_basic(lex, &j, *i, &str);
		else if (lex[j].type == QUOTE && (lex[j + 1].value == ' ' \
			|| lex[j + 1].value == '\t'))
		{
			j++;
			break ;
		}
		else if ((lex[j].type == QUOTE || lex[j].type == NORMAL) && \
				lex[j].value != ' ' && lex[j].value != '\t' && lex[j + 1].type)
			j++;
		else
			break ;
	}
	if (str)
		return ((*i) = j - 1, new_token_item(str, TOKEN));
	return (NULL);
}
