/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 17:16:47 by aagathe           #+#    #+#             */
/*   Updated: 2023/10/04 14:16:07 by aagathe          ###   ########.fr       */
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

void	close_pfd(int nb_cmds, int pfd[4], t_cmd *cmds)
{
	if (!pfd)
		return ;
	if (!cmds->next)
	{
		if (nb_cmds > 1)
		{
			close(pfd[nb_cmds % 2 * 2]);
			close(pfd[nb_cmds % 2 * 2 + 1]);
		}
	}
	else
	{
		close(pfd[0]);
		close(pfd[1]);
		if (nb_cmds > 1)
		{
			close(pfd[2]);
			close(pfd[3]);
		}
	}
}

void	close_files(t_cmd *cmds, int pfd[4], int nb_cmds)
{
	int		redr;
	t_redr	*redr_cpy;

	close_pfd(nb_cmds, pfd, go_to_cmds(cmds, nb_cmds));
	redr = 0;
	while (cmds)
	{
		redr_cpy = cmds->redr_in;
		if (redr)
			redr_cpy = cmds->redr_out;
		while (redr_cpy)
		{
			if (redr_cpy->fd > 0)
				close(redr_cpy->fd);
			if (redr_cpy->pfd[0] > 0)
				close(redr_cpy->pfd[0]);
			if (redr_cpy->pfd[1] > 0)
				close(redr_cpy->pfd[1]);
			redr_cpy = redr_cpy->next;
		}
		if (redr)
			cmds = cmds->next;
		if (redr++)
			redr = 0;
	}
}

void	unswitch_files(t_cmd *cmds, int action)
{
	if (action)
	{
		if (cmds->redr_in)
			dup2(cmds->old_stdin, 0);
		if (cmds->redr_out)
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

void	switch_files(t_cmd *cmds, int id_cmd, int pfd[4])
{
	t_redr	*redr_in;
	t_redr	*redr_out;

	if (cmds->redr_in)
	{
		redr_in = cmds->redr_in;
		while (redr_in->next)
			redr_in = redr_in->next;
		dup2(redr_in->fd, 0);
	}
	else if (id_cmd > 1 && id_cmd % 2)
		dup2(pfd[2], 0);
	else if (id_cmd > 1)
		dup2(pfd[0], 0);
	if (cmds->redr_out)
	{
		redr_out = cmds->redr_out;
		while (redr_out->next)
			redr_out = redr_out->next;
		dup2(redr_out->fd, 1);
	}
	else if (cmds->next && id_cmd % 2)
		dup2(pfd[1], 1);
	else if (cmds->next)
		dup2(pfd[3], 1);
}
