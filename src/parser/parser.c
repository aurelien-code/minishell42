/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:00:11 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/04 03:14:10 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_tokens	*tokens)
{
	char	*str;

	str = tokens->value;
	if (!str)
		return (0);
	if (!ft_strncmp(str, "echo", 5))
		return (1);
	else if (!ft_strncmp(str, "cd", 3))
		return (2);
	else if (!ft_strncmp(str, "env", 4))
		return (3);
	else if (!ft_strncmp(str, "export", 7))
		return (4);
	else if (!ft_strncmp(str, "pwd", 4))
		return (5);
	else if (!ft_strncmp(str, "unset", 6))
		return (6);
	else if (!ft_strncmp(str, "exit", 5))
		return (7);
	else
		return (0);
}

void	dbg_print_cmd(t_cmd *cmds)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (cmds)
	{
		printf("command #%d\n", i);
		printf("	-> is_builtin = %d\n	-> cmd = ", cmds->is_builtin);
		while (cmds->cmd[j])
		{
			printf("%s ", cmds->cmd[j]);
			j++;
		}
		printf("\n");
		if (cmds->redr_in)
			printf("	-> redr_in = (%d)%s\n", cmds->redr_in->type, \
				cmds->redr_in->filename);
		if (cmds->redr_out)
			printf("	-> redr_out = (%d)%s\n", cmds->redr_out->type, \
				cmds->redr_out->filename);
		j = 0;
		i++;
		cmds = cmds->next;
	}
}

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

t_cmd	*parser(t_tokens *tokens)
{
	t_cmd	*head_cmds;
	t_cmd	*current_cmd;

	head_cmds = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		current_cmd = init_or_get_cmd(&head_cmds, current_cmd);
		if (tokens->type == TOKEN)
		{
			add_to_cmd(current_cmd, tokens->value);
			if (!current_cmd->cmd[1] && tokens->value)
				current_cmd->is_builtin = is_builtin(tokens);
		}
		else if (tokens->type >= D_REDIR_L && tokens->type <= S_REDIR_R)
			tokens = handle_redirection(current_cmd, tokens);
		else if (tokens->type == T_PIPE && (!current_cmd || !current_cmd->cmd))
			return (throw_parsing_error(NULL, NULL, head_cmds, NO_PIPE_ENTRY));
		else if (tokens->type == T_PIPE && !tokens->next)
			return (throw_parsing_error(NULL, NULL, head_cmds, NO_OUT_CMD));
		else if (tokens->type == T_PIPE)
			current_cmd = NULL;
		if (!tokens)
			return (NULL);
		tokens = tokens->next;
	}
	dbg_print_cmd(head_cmds);
	return (head_cmds);
}
