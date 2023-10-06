/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 17:16:47 by aagathe           #+#    #+#             */
/*   Updated: 2023/10/06 20:36:21 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_pipe(int pfd[4], int nb_cmds, t_cmd *next)
{
	const int	modulo = nb_cmds % 2;

	if (nb_cmds > 2 - modulo)
	{
		close(pfd[2 - (modulo * 2)]);
		close(pfd[3 - (modulo * 2)]);
	}
	if (next && pipe(pfd + 2 - (modulo * 2)))
	{
		perror("minishell: pipe error");
		if (nb_cmds > 1)
		{
			close(pfd[modulo * 2]);
			close(pfd[1 + (modulo * 2)]);
		}
		return (1);
	}
	return (0);
}

void	close_pfd(t_cmd *cmds, int pfd[4])
{
	if (cmds->nb_cmd == 1 && !cmds->next)
		return ;
	if (!cmds->next)
	{
		if (cmds->nb_cmd > 1)
		{
			close(pfd[cmds->nb_cmd % 2 * 2]);
			close(pfd[cmds->nb_cmd % 2 * 2 + 1]);
		}
	}
	else
	{
		close(pfd[0]);
		close(pfd[1]);
		if (cmds->nb_cmd > 1)
		{
			close(pfd[2]);
			close(pfd[3]);
		}
	}
}

void	close_files(t_cmd *cmds, int pfd[4])
{
	t_redr	*redr;

	close_pfd(cmds, pfd);
	redr = cmds->redr;
	while (redr)
	{
		if (redr->fd > 0)
			close(redr->fd);
		if (redr->pfd[0] > 0)
			close(redr->pfd[0]);
		if (redr->pfd[1] > 0)
			close(redr->pfd[1]);
		redr = redr->next;
	}
}

void	unswitch_files(t_cmd *cmds, int action)
{
	if (action)
	{
		dup2(cmds->old_stdin, 0);
		dup2(cmds->old_stdout, 1);
		close(cmds->old_stdin);
		close(cmds->old_stdout);
	}
	else
	{
		cmds->old_stdin = dup(0);
		cmds->old_stdout = dup(1);
	}
}

void	switch_files(t_cmd *cmds, int pfd[4])
{
	t_redr	*redr;
	int		redr_in;
	int		redr_out;

	redr_in = 0;
	redr_out = 0;
	redr = cmds->redr;
	while (redr)
	{
		if (redr->type == S_REDIR_L || redr->type == D_REDIR_L)
			redr_in = redr->fd;
		else
			redr_out = redr->fd;
		redr = redr->next;
	}
	if (redr_in)
		dup2(redr_in, 0);
	else if (cmds->nb_cmd > 1)
		dup2(pfd[cmds->nb_cmd % 2 * 2], 0);
	if (redr_out)
		dup2(redr_out, 1);
	else if (cmds->next && cmds->nb_cmd % 2)
		dup2(pfd[1], 1);
	else if (cmds->next)
		dup2(pfd[3], 1);
}
