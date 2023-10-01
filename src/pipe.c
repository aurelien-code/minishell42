/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:33:45 by aagathe           #+#    #+#             */
/*   Updated: 2023/10/01 16:58:41 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*go_to_cmds(t_cmd *cmds, int nb_cmds)
{
	while (--nb_cmds)
		cmds = cmds->next;
	return (cmds);
}

void	entry_error(const char *filename)
{
	char	*error;
	char	*error2;
	char	*nb_line;

	nb_line = ft_itoa(history_size(0));
	error = ft_strjoin("minishell: warning : here-document at the line ",
			nb_line);
	free(nb_line);
	error2 = ft_strjoin(error, " delimited by end-of-file (wanted `");
	free(error);
	error = ft_strjoin(error2, filename);
	free(error2);
	error2 = ft_strjoin(error, "')");
	free(error);
	ft_putendl_fd(error2, 2);
	free(error2);
}

void	write_entry(t_cmd *cmds)
{
	const int	name_size = ft_strlen(cmds->redr_in->filename);
	char		*buffer;
	int			pfd[2];

	if (pipe(pfd) < 0)
	{
		perror(TEMP_FILE_ERR);
		return ;
	}
	cmds->redr_in->pfd[0] = pfd[0];
	cmds->redr_in->pfd[1] = pfd[1];
	cmds->redr_in->fd = pfd[0];
	buffer = NULL;
	buffer = readline("> ");
	while (buffer)
	{
		if (!ft_strncmp(buffer, cmds->redr_in->filename, name_size + 1))
			break ;
		write(pfd[1], buffer, ft_strlen(buffer));
		write(pfd[1], "\n", 1);
		free(buffer);
		buffer = readline("> ");
	}
	if (!buffer)
		entry_error(cmds->redr_in->filename);
}

int	open_redr_in(t_cmd *cmds)
{
	int		ret;
	t_redr	*redr_in;
	char	*error;

	ret = 0;
	redr_in = cmds->redr_in;
	while (cmds->redr_in)
	{
		if (cmds->redr_in->type == S_REDIR_L)
			cmds->redr_in->fd = open(cmds->redr_in->filename, O_RDONLY);
		else
			write_entry(cmds);
		if (cmds->redr_in->fd < 0 && cmds->redr_in->type == 4 && ++ret)
		{
			error = ft_strjoin("minishell: ", cmds->redr_in->filename);
			perror(error);
			free(error);
		}
		cmds->redr_in = cmds->redr_in->next;
	}
	cmds->redr_in = redr_in;
	return (ret);
}

int	open_redr_out(t_cmd *cmds)
{
	int		ret;
	t_redr	*redr_out;
	char	*error;

	ret = 0;
	redr_out = cmds->redr_out;
	while (cmds->redr_out)
	{
		if (cmds->redr_out->type == S_REDIR_R)
			cmds->redr_out->fd = open(cmds->redr_out->filename,
					O_CREAT | O_TRUNC | O_WRONLY, 0660);
		else
			cmds->redr_out->fd = open(cmds->redr_out->filename,
					O_CREAT | O_WRONLY | O_APPEND, 0660);
		if (cmds->redr_out->fd < 0 && ++ret)
		{
			error = ft_strjoin("minishell: ", cmds->redr_out->filename);
			perror(error);
			free(error);
		}
		cmds->redr_out = cmds->redr_out->next;
	}
	cmds->redr_out = redr_out;
	return (ret);
}

int	open_files(t_cmd *cmds)
{
	int		ret;

	ret = 0;
	while (cmds)
	{
		ret += open_redr_in(cmds);
		ret += open_redr_out(cmds);
		cmds = cmds->next;
	}
	return (ret);
}

void	close_pfd(int nb_cmds, int pfd[4], t_cmd *cmds)
{
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

char	*check_path(char *cmd, char **pathes)
{
	char	*path;
	char	*slash;

	while (*pathes)
	{
		slash = ft_strjoin(*pathes++, "/");
		path = ft_strjoin(slash, cmd);
		free(slash);
		if (!access(path, F_OK))
			return (path);
		free(path);
	}
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	return (NULL);
}

char	**find_pathes(char *env[])
{
	while (*env && ft_strncmp(*env, "PATH", 4))
		env++;
	return (ft_split(*env + 5, ':'));
}

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

int	try_fork(void)
{
	int	i;
	int	pid;

	i = 4;
	pid = fork();
	while (pid < 0 && i--)
	{
		perror("minishell: fork: retry");
		pid = fork();
	}
	if (pid < 0)
		perror("minishell: fork");
	return (pid);
}

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
		return (ft_exit(cmds, pfd));
	return (0);
}

void	free_pathes(char **pathes)
{
	int	i;

	i = 0;
	while ((pathes[i]))
		free(pathes[i++]);
	free(pathes);
	return ;
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
		error = ft_strjoin(cmd[0], " : command not found");
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
	switch_files(cmds_cpy, nb_cmds, pfd);
	close_files(cmds, pfd, nb_cmds);
	if (cmds->is_builtin)
		ret = launch_builtin(cmds_cpy, env, pfd);
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
