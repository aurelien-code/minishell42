/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 22:57:19 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/03 00:36:02 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_expand(t_lexer *lexer_arr, int *i, char **env, char **str)
{
	t_tokens	*tk;
	char		*tmp;

	tk = expand(lexer_arr, i, env);
	if (*str)
	{
		tmp = *str;
		*str = ft_strjoin(tmp, tk->value);
		free(tmp);
	}
	else
		*str = ft_strdup(tk->value);
	free_tokens(tk);
}

void	handle_quote(t_lexer *lexer_arr, int *i, char **env, char **str)
{
	t_tokens	*tk;
	char		*tmp;

	tk = get_quote_token(lexer_arr, i, env);
	(*i)++;
	if (*str && tk && tk->value)
	{
		tmp = *str;
		*str = ft_strjoin(tmp, tk->value);
		free(tmp);
	}
	free_tokens(tk);
}

void	handle_other(t_lexer *lexer_arr, int *i, char **str)
{
	char		*tmp;

	if (*str)
	{
		tmp = *str;
		*str = ft_strjoin(tmp, &lexer_arr[*i].value);
		free(tmp);
	}
	else
		*str = ft_strdup(&lexer_arr[*i].value);
	(*i)++;
}

t_tokens	*get_word_token(t_lexer *lexer_arr, int *i, char **env)
{
	char		*str;

	str = NULL;
	while (lexer_arr[*i].value && lexer_arr[*i].value != ' ' && \
			lexer_arr[*i].value != '\t')
	{
		if (lexer_arr[*i].type == EXPAND)
			handle_expand(lexer_arr, i, env, &str);
		else if (lexer_arr[*i].type == QUOTE)
			handle_quote(lexer_arr, i, env, &str);
		else
			handle_other(lexer_arr, i, &str);
	}
	if (str)
		return (new_token_item(str, TOKEN));
	else
		return (NULL);
}
