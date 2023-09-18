/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:17:04 by aumarin           #+#    #+#             */
/*   Updated: 2023/09/18 15:00:50 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*handle_double_redirect(t_lexer *lexer_arr, int *i, int j)
{
	t_tokens	*token;

	if (lexer_arr[*i].value != lexer_arr[*i + 1].value)
	{
		(*i) = j - 1;
		return (NULL);
	}
	if (lexer_arr[*i].value == '<')
		token = (new_token_item(NULL, D_REDIR_L));
	else
		token = (new_token_item(NULL, D_REDIR_R));
	(*i) = j - 1;
	return (token);
}

t_tokens	*handle_single_redirect(t_lexer *lexer_arr, int *i)
{
	if (lexer_arr[*i].value == '<')
		return (new_token_item(NULL, S_REDIR_L));
	else
		return (new_token_item(NULL, S_REDIR_R));
}

t_tokens	*get_redirect_token(t_lexer *lexer_arr, int *i)
{
	int			redir_size;
	int			j;

	j = *i;
	redir_size = 0;
	while (lexer_arr[j].type == REDIRECT)
	{
		redir_size++;
		j++;
	}
	if (redir_size > 2)
	{
		(*i) = j - 1;
		printf("Too many redirection symbols\n");
		return (NULL);
	}
	else if (redir_size == 2)
		return (handle_double_redirect(lexer_arr, i, j));
	else
		return (handle_single_redirect(lexer_arr, i));
	return (NULL);
}

static void	assign_redirection(t_cmd **command, t_redr *new_redr)
{
	t_redr	*tmp;

	if (new_redr->type == D_REDIR_L || new_redr->type == S_REDIR_L)
		tmp = (*command)->redr_in;
	else
		tmp = (*command)->redr_out;
	if (!tmp)
		tmp = new_redr;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redr;
	}
}

int	handle_redirection(t_tokens **tokens, t_cmd **command)
{
	t_redr	*new_redr;

	new_redr = ft_calloc(1, sizeof(t_redr));
	if (!new_redr)
		return (0);
	new_redr->fd = -1;
	new_redr->type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN)
	{
		free(new_redr);
		return (0);
	}
	new_redr->filename = ft_strdup((*tokens)->value);
	assign_redirection(command, new_redr);
	return (1);
}
