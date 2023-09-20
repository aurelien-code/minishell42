/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:35:34 by aumarin           #+#    #+#             */
/*   Updated: 2023/09/20 16:27:05 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokens *tokens)
{
	t_tokens	*current;
	t_tokens	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		if (current)
			free(current);
		current = next;
	}
}

void	free_redirs(t_redr	*redr)
{
	t_redr	*tmp;
	tmp = NULL;
	while (redr)
	{
		if (redr->filename)
			free(redr->filename);
		tmp = redr;
		redr = redr->next;
		if (tmp)
			free(tmp);
	}
}

void	free_commands(t_cmd *commands)
{
	t_cmd	*tmp_cmds;
	int		i;

	tmp_cmds = NULL;
	i = 0;
	while (commands)
	{
		if (commands->cmd)
		{
			while (commands->cmd[i])
			{
				free(commands->cmd[i]);
				i++;
			}
			free(commands->cmd);
		}
		if (commands->res)
			free(commands->res);
		if (commands->redr_in)
			free_redirs(commands->redr_in);
		if (commands->redr_out)
			free_redirs(commands->redr_out);
		tmp_cmds = commands;
		commands = commands->next;
		free(tmp_cmds);
	}
}
