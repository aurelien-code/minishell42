/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 22:57:19 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/04 03:55:27 by aumarin          ###   ########.fr       */
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
		if (!tk->value)
			tk->value = ft_strdup("");
		*str = ft_strjoin(tmp, tk->value);
		free(tmp);
	}
	else
		*str = ft_strdup(tk->value);
	free_tokens(tk);
}

int	handle_quote(t_lexer *lexer_arr, int *i, char **env, char **str)
{
	t_tokens	*tk;
	char		*tmp;

	tk = get_quote_token(lexer_arr, i, env);
	(*i)++;
	if (!tk)
		return (0);
	if (*str && tk && tk->value)
	{
		tmp = *str;
		*str = ft_strjoin(tmp, tk->value);
		free(tmp);
	}
	free_tokens(tk);
	return (1);
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
		{
			if (!handle_quote(lexer_arr, i, env, &str))
			{
				if (str)
					free(str);
				return (NULL);
			}
		}
		else
			handle_other(lexer_arr, i, &str);
		if (lexer_arr[*i].type == PIPE)
		{
			(*i)--;
			break ;
		}
	}
	if (str)
		return (new_token_item(str, TOKEN));
	else
		return (new_token_item(NULL, 0));
}
