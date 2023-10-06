/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:00:11 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/06 19:33:54 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_cmd(t_cmd *cmd, char *value)
{
	int		i;
	int		j;
	char	**new_cmd;

	i = 0;
	while (cmd->cmd && cmd->cmd[i])
		i++;
	new_cmd = ft_calloc(i + 2, sizeof(char *));
	j = 0;
	while (j < i)
	{
		new_cmd[j] = cmd->cmd[j];
		j++;
	}
	if (value)
		new_cmd[j] = ft_strdup(value);
	else
		new_cmd[i] = NULL;
	free(cmd->cmd);
	cmd->cmd = new_cmd;
}

t_cmd	*init_or_get_cmd(t_cmd **head_cmds, t_cmd *current_cmd)
{
	t_cmd	*tmp;

	tmp = NULL;
	if (!current_cmd)
	{
		current_cmd = ft_calloc(1, sizeof(t_cmd));
		current_cmd->pid = -1;
		if (!(*head_cmds))
			*head_cmds = current_cmd;
		else
		{
			tmp = *head_cmds;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = current_cmd;
		}
	}
	return (current_cmd);
}

int	handle_pipe_case(t_tokens *tokens, t_cmd **current_cmd, t_cmd **head_cmds)
{
	if (tokens->type == T_PIPE && (!(*current_cmd) || \
		(!(*current_cmd)->cmd && !(*current_cmd)->redr)))
	{
		throw_parsing_error(NULL, NULL, *head_cmds, NO_PIPE_ENTRY);
		return (0);
	}
	else if (tokens->type == T_PIPE && !tokens->next)
	{
		throw_parsing_error(NULL, NULL, *head_cmds, NO_OUT_CMD);
		return (0);
	}
	else if (tokens->type == T_PIPE)
		*current_cmd = NULL;
	return (1);
}

t_tokens	*handle_tok(t_cmd **current, t_cmd **head, t_tokens *tok, int *i)
{
	*current = init_or_get_cmd(head, *current);
	if (tok->type == TOKEN)
	{
		add_to_cmd(*current, tok->value);
		if (!(*current)->cmd[1] && tok->value)
			(*current)->is_builtin = is_builtin(tok);
	}
	else if (tok->type >= D_REDIR_L && tok->type <= S_REDIR_R)
		tok = handle_redirection(*current, tok);
	else if (tok->type == T_PIPE \
		&& !handle_pipe_case(tok, current, head))
		return (NULL);
	return (tok);
}

t_cmd	*parser(t_tokens *tokens)
{
	t_cmd	*head_cmds;
	t_cmd	*current_cmd;

	head_cmds = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		tokens = handle_tok(&current_cmd, &head_cmds, tokens, &i);
		if (!tokens)
			return (NULL);
		tokens = tokens->next;
	}
	return (head_cmds);
}
