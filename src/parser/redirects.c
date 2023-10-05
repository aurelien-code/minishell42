/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:17:04 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/05 23:55:18 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

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
		return (throw_parsing_error(NULL, NULL, NULL, TOO_MANY_REDIRS));
	}
	else if (redir_size == 2)
		return (handle_double_redirect(lexer_arr, i, j));
	else
	{
		if (lexer_arr[*i].value == '<')
			return (new_token_item(NULL, S_REDIR_L));
		else
			return (new_token_item(NULL, S_REDIR_R));
	}
	return (NULL);
}

void	add_input_redirection(t_cmd *cmd, t_redr *redirection)
{
	t_redr	*tmp;

	redirection->direction = 1;
	if (!cmd->redr)
	{
		cmd->redr = redirection;
		return ;
	}
	tmp = cmd->redr;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redirection;
}

void	add_output_redirection(t_cmd *cmd, t_redr *redirection)
{
	t_redr	*tmp;

	redirection->direction = 2;
	if (!cmd->redr)
	{
		cmd->redr = redirection;
		return ;
	}
	tmp = cmd->redr;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redirection;
}

t_tokens	*handle_redirection(t_cmd *cmd, t_tokens *tokens)
{
	t_redr	*redirection;

	redirection = ft_calloc(1, sizeof(t_redr));
	redirection->type = tokens->type;
	redirection->fd = -1;
	redirection->pfd[0] = -1;
	redirection->pfd[1] = -1;
	tokens = tokens->next;
	if (!tokens || tokens->type != TOKEN)
	{
		free(redirection);
		ft_putstr_fd(NO_FILE_TO_REDR, 2);
		free_commands(cmd);
		g_exit_code = 2;
		return (NULL);
	}
	redirection->filename = ft_strdup(tokens->value);
	if (redirection->type == D_REDIR_L || redirection->type == S_REDIR_L)
		add_input_redirection(cmd, redirection);
	else
		add_output_redirection(cmd, redirection);
	return (tokens);
}
