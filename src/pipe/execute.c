/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 17:08:43 by aagathe           #+#    #+#             */
/*   Updated: 2023/10/02 14:18:41 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_builtin(t_cmd *cmds, char ***env, int pfd[4])
{
	if (cmds->is_builtin == 1)
		return (ft_echo(cmds));
	else if (cmds->is_builtin == 2)
		return (ft_cd(cmds, *env));
	else if (cmds->is_builtin == 3)
		return (ft_env(cmds, *env));
	else if (cmds->is_builtin == 4)
		return (ft_export(cmds, env));
	else if (cmds->is_builtin == 5)
		return (ft_pwd(cmds));
	else if (cmds->is_builtin == 6)
		return (ft_unset(cmds, env));
	else if (cmds->is_builtin == 7)
		return (ft_exit(cmds, pfd, *env));
	return (0);
}

int	launch_cmd_next(char *path, char **cmd, char **env)
{
	char	*error;

	if (path)
	{
		execve(path, cmd, env);
		perror(path);
		free(path);
		return (126);
	}
	else
	{
		error = ft_strjoin(cmd[0], ": command not found");
		ft_putendl_fd(error, 2);
		free(error);
		return (127);
	}
}

int	launch_cmd(t_cmd *cmds, int nb_cmds, int pfd[4], char ***env)
{
	int		ret;
	char	*path;
	char	**pathes;
	t_cmd	*cmds_cpy;

	cmds_cpy = go_to_cmds(cmds, nb_cmds);
	pathes = find_pathes(*env);
	path = check_path(cmds_cpy->cmd[0], pathes);
	free_pathes(pathes);
	unswitch_files(cmds, pfd, 0);
	switch_files(cmds_cpy, nb_cmds, pfd);
	close_files(cmds, pfd, nb_cmds);
	if (cmds->is_builtin)
	{
		ret = launch_builtin(cmds_cpy, env, pfd);
		unswitch_files(cmds, pfd, 1);
	}
	else
		ret = launch_cmd_next(path, cmds_cpy->cmd, *env);
	if (pfd)
	{
		free_commands(cmds);
		exit(ret);
	}
	return (ret);
}

int	check_status(int wstatus)
{
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
	int		pid;
	int		wstatus;
	int		nb_cmds;
	t_cmd	*cmds_cpy;

	nb_cmds = 0;
	if (open_files(cmds))
		return (close_files(cmds, NULL, nb_cmds), 1);
	cmds_cpy = cmds;
	if (cmds->is_builtin && !cmds->next)
		return (launch_cmd(cmds, 1, NULL, env));
	while (cmds_cpy && ++nb_cmds)
	{
		if (open_pipe(pfd, nb_cmds, cmds_cpy->next))
			return (129);
		pid = try_fork();
		if (pid < 0)
			return (254);
		if (pid == 0)
			launch_cmd(cmds, nb_cmds, pfd, env);
		cmds_cpy = cmds_cpy->next;
	}
	close_files(cmds, pfd, nb_cmds);
	while (nb_cmds--)
		waitpid(-1, &wstatus, 0);
	return (check_status(wstatus));
}
