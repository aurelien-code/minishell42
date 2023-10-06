/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:29:32 by aagathe           #+#    #+#             */
/*   Updated: 2023/10/06 20:03:31 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_fork(char **pathes, char **env, t_cmd *cmds, int ret)
{
	if (pathes)
		free_pathes(pathes);
	free_pathes(env);
	free_commands(cmds);
	exit(ret);
}

void	check_directory(char *path)
{
	char		*err;
	char		*err2;
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			err = ft_strjoin("minishell: ", path);
			err2 = ft_strjoin(err, ": Is a directory");
			ft_putendl_fd(err2, 2);
			free(err);
			free(err2);
		}
		else
		{
			err = ft_strjoin("minishell: ", path);
			err2 = ft_strjoin(err, ": Permission denied");
			ft_putendl_fd(err2, 2);
			free(err);
			free(err2);
		}
	}
	else
		perror("stat");
}

int	check_access(char *path, char **pathes)
{
	char	*err;

	if (errno == EACCES && ft_strchr(path, '/'))
	{
		check_directory(path);
		free(path);
		return (126);
	}
	else
	{
		if (ft_strchr(path, '/') || !pathes)
		{
			err = ft_strjoin("minishell: ", path);
			perror(err);
			free(err);
		}
		else
		{
			err = ft_strjoin(path, ": command not found\n");
			ft_putstr_fd(err, 2);
			free(err);
		}
		free(path);
		return (127);
	}
}

int	launch_builtin_solo(t_cmd *cmds, char ***env)
{
	int	ret;

	if (open_files(cmds, NULL))
		return (1);
	unswitch_files(cmds, 0);
	switch_files(cmds, NULL);
	close_files(cmds, NULL);
	ret = 0;
	if (cmds->is_builtin == 1)
		ret = ft_echo(cmds);
	else if (cmds->is_builtin == 2)
		ret = ft_cd(cmds, *env);
	else if (cmds->is_builtin == 3)
		ret = ft_env(cmds, *env);
	else if (cmds->is_builtin == 4)
		ret = ft_export(cmds, env);
	else if (cmds->is_builtin == 5)
		ret = ft_pwd(cmds);
	else if (cmds->is_builtin == 6)
		ret = ft_unset(cmds, env);
	else if (cmds->is_builtin == 7)
		ret = ft_exit(cmds, *env, 0, NULL);
	unswitch_files(cmds, 1);
	return (ret);
}

int	launch_builtin(t_cmd *cmds, char ***env, char *path, int pfd[4])
{
	int	ret;

	free(path);
	ret = 0;
	if (cmds->is_builtin == 1)
		ret = ft_echo(cmds);
	else if (cmds->is_builtin == 2)
		ret = ft_cd(cmds, *env);
	else if (cmds->is_builtin == 3)
		ret = ft_env(cmds, *env);
	else if (cmds->is_builtin == 4)
		ret = ft_export(cmds, env);
	else if (cmds->is_builtin == 5)
		ret = ft_pwd(cmds);
	else if (cmds->is_builtin == 6)
		ret = ft_unset(cmds, env);
	else if (cmds->is_builtin == 7)
		ret = ft_exit(cmds, *env, 1, pfd);
	return (ret);
}

void	launch_cmd(t_cmd *cmds, int pfd[4], char ***env, t_cmd *start_cmds)
{
	int		ret;
	char	*path;
	char	**pathes;

	if (open_files(cmds, pfd))
		exit_fork(NULL, *env, start_cmds, 1);
	switch_files(cmds, pfd);
	//if (!cmds->is_builtin)
		close_files(cmds, pfd);
	if (!cmds->cmd)
		exit_fork(NULL, *env, start_cmds, 0);
	pathes = find_pathes(*env);
	path = check_path(cmds->cmd[0], pathes);
	if (cmds->is_builtin)
	{
		ret = launch_builtin(cmds, env, path, pfd);
		//close_files(cmds, pfd);
	}
	else if (ft_strchr(path, '/') || !pathes)
		execve(path, cmds->cmd, *env);
	if (!cmds->is_builtin)
		ret = check_access(path, pathes);
	exit_fork(pathes, *env, start_cmds, ret);
}
