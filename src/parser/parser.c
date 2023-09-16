/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:00:11 by aumarin           #+#    #+#             */
/*   Updated: 2023/09/16 12:53:30 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "echo", 4))
		return (1);
	else if (!ft_strncmp(str, "cd", 2))
		return (1);
	else if (!ft_strncmp(str, "env", 3))
		return (1);
	else if (!ft_strncmp(str, "export", 5))
		return (1);
	else if (!ft_strncmp(str, "pwd", 3))
		return (1);
	else if (!ft_strncmp(str, "unset", 5))
		return (1);
	else
		return (0);
}

t_redr	*process_redirects(t_tokens **tokens, t_cmd **command)
{
	t_redr	*redirection;

	redirection = NULL;
	while (*tokens && (*tokens)->type != T_PIPE)
	{
		if ((*tokens)->type > 1 && (*tokens)->type < 7)
		{
			if (!handle_redirection(tokens, &redirection, command))
				return (NULL);
		}
		*tokens = (*tokens)->next;
	}
	return (redirection);
}

t_cmd	*process_command(t_tokens **tokens, int cmd_size)
{
	int			i;
	t_cmd		*command;

	command = ft_calloc(1, sizeof(t_cmd));
	command->cmd = ft_calloc(cmd_size + 1, sizeof(char *));
	if (!command->cmd)
		return (NULL);
	i = 0;
	while ((*tokens)->type != T_PIPE)
	{
		if (i == 0)
			command->is_builtin = is_builtin((*tokens)->value);
		if ((*tokens)->type != T_PIPE && (*tokens)->type != TOKEN)
			process_redirects(tokens, &command);
		command->cmd[i] = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
		i++;
	}
	return (command);
}

void	add_cmd_item(t_cmd **cmds, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!(*cmds))
		(*cmds) = new_cmd;
	else
	{
		tmp = (*cmds);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
	}
}

t_cmd	*parser(t_tokens *tokens)
{
	t_cmd		*cmds;
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = tokens;
	while (tokens)
	{
		if (tokens->type == T_PIPE)
			add_cmd_item(&cmds, process_command(&tmp, i));
		tokens = tokens->next;
		i++;
	}
	return (cmds);
}
