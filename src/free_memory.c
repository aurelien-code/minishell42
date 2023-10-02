/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:35:34 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/02 11:31:14 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokens *tokens)
{
	t_tokens	*current;
	t_tokens	*next;

	if (!tokens)
		return ;
	current = tokens;
	while (current)
	{
		if (current->next)
			next = current->next;
		else
			next = NULL;
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
	if (!redr)
		return ;
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
	t_cmd	*tmp;
	int		i;

	while (commands)
	{
		tmp = commands;
		commands = commands->next;
		if (tmp->cmd)
		{
			i = 0;
			while (tmp->cmd[i])
			{
				free(tmp->cmd[i]);
				i++;
			}
			free(tmp->cmd);
		}
		if (tmp->res)
			free(tmp->res);
		if (tmp->redr_in)
			free_redirs(tmp->redr_in);
		if (tmp->redr_out)
			free_redirs(tmp->redr_out);
		free(tmp);
	}
}
