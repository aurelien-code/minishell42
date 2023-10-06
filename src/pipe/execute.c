/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 17:08:43 by aagathe           #+#    #+#             */
/*   Updated: 2023/10/06 20:17:45 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_status(t_cmd *cmds)
{
	int	wstatus;

	while (cmds)
	{
		waitpid(cmds->pid, &wstatus, 0);
		cmds = cmds->next;
	}
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
	{
		if (WTERMSIG(wstatus) == 2)
		{
			write(2, "\n", 1);
			rl_on_new_line();
			return (130);
		}
		else if (WTERMSIG(wstatus) == 3)
		{
			write(2, "Quit (core dumped)\n", 19);
			rl_on_new_line();
			return (131);
		}
	}
	return (-1);
}

int	executer(t_cmd *cmds, char **env[])
{
	int		pfd[4];
	t_cmd	*cmds_cpy;
	int		nb_cmd;

	cmds_cpy = cmds;
	if ((cmds->is_builtin || !cmds->cmd) && !cmds->next)
		return (launch_builtin_solo(cmds, env));
	nb_cmd = 0;
	while (cmds_cpy && ++nb_cmd)
	{
		cmds_cpy->nb_cmd = nb_cmd;
		if (open_pipe(pfd, cmds_cpy->nb_cmd, cmds_cpy->next))
			return (129);
		cmds_cpy->pid = try_fork();
		if (cmds_cpy->pid < 0)
			return (254);
		if (cmds_cpy->pid == 0)
			sig_setup(2);
		if (cmds_cpy->pid == 0)
			launch_cmd(cmds_cpy, pfd, env, cmds);
		if (!cmds_cpy->next)
			close_pfd(cmds_cpy, pfd);
		cmds_cpy = cmds_cpy->next;
	}
	return (check_status(cmds));
}
