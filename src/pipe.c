/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:33:45 by aagathe           #+#    #+#             */
/*   Updated: 2023/09/20 17:16:53 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	entry_error(char *filename)
{
	char	*error;
	char	*error2;
	char	*nb_line;

	nb_line = ft_itoa(25/*nb_line_history*/);
	error = ft_strjoin("minishell: warning : « here-document » at the line ",
			nb_line);
	free(nb_line);
	error2 = ft_strjoin(error, " delimited by EOF (instead of `");
	free(error);
	error = ft_strjoin(error2, filename);
	free(error2);
	error2 = ft_strjoin(error, "')");
	free(error);
	ft_putendl_fd(error2, 2);
	free(error2);
}

void	write_entry(char *filename, int fd)
{
	int		name_size;
	char	*buffer;

	buffer = NULL;
	name_size = ft_strlen(filename);
	buffer = readline("> ");
	while (buffer)
	{
		if (!ft_strncmp(buffer, filename, name_size + 1))
			break ;
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
		buffer = readline("> ");
	}
	if (!buffer)
		entry_error(filename); // VERIFIER PHRASE ANGLAIS
}

int	open_files(t_cmd *cmds, int pfd[2])
{
	int		ret;
	char	*error;
	t_redr	*redr_in;
	t_redr	*redr_out;

	ret = 0;
	while (cmds)
	{
		redr_in = cmds->redr_in;
		while (cmds->redr_in)
		{
			if (cmds->redr_in->type == S_REDIR_L)
				cmds->redr_in->fd = open(cmds->redr_in->filename, O_RDONLY);
			else
			{
				write_entry(cmds->redr_in->filename, pfd[3]);
			}
			if (cmds->redr_in->fd < 0 && ++ret)
			{
				error = ft_strjoin("minishell: ", cmds->redr_in->filename);
				perror(error);
				free(error);
			}
			cmds->redr_in = cmds->redr_in->next;
		}
		cmds->redr_in = redr_in;
		redr_out = cmds->redr_out;
		while (cmds->redr_out)
		{
			if (cmds->redr_out->type == S_REDIR_R)
				cmds->redr_out->fd = open(cmds->redr_out->filename, O_CREAT | O_TRUNC | O_WRONLY, 0660);
			else
				cmds->redr_out->fd = open(cmds->redr_out->filename, O_WRONLY | O_APPEND);
			if (cmds->redr_out->fd < 0 && ++ret)
			{
				error = ft_strjoin("minishell: ", cmds->redr_out->filename);
				perror(error);
				free(error);
			}
			cmds->redr_out = cmds->redr_out->next;
		}
		cmds->redr_out = redr_out;
		cmds = cmds->next;
	}
	return (ret);
}

void	close_files(t_cmd *cmds, int pfd[4])
{
	t_redr	*redr_in;
	t_redr	*redr_out;

	while (cmds)
	{
		redr_in = cmds->redr_in;
		while (cmds->redr_in)
		{
			if (cmds->redr_in->fd > 0)
				close(cmds->redr_in->fd);
			cmds->redr_in = cmds->redr_in->next;
		}
		cmds->redr_in = redr_in;
		redr_out = cmds->redr_out;
		while (cmds->redr_out)
		{
			if (cmds->redr_out->fd > 0)
				close(cmds->redr_out->fd);
			cmds->redr_out = cmds->redr_out->next;
		}
		cmds->redr_out = redr_out;
		cmds = cmds->next;
	}
	close(pfd[0]);
	close(pfd[1]);
	close(pfd[2]);
	close(pfd[3]);
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
		dup2(redr_out->fd, 0);
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

char **find_pathes(char *env[])
{
	while (*env && ft_strncmp(*env, "PATH", 4))
		env++;
	if (*env)
		*env += 5;
	return (ft_split(*env, ':'));
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

int	try_fork()
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

void	launch_cmd(t_cmd *cmds, t_cmds *cmds->cpy, char **pathes, int pfd[4])
{
	char	*path;

	path = check_path(cmds_cpy, pathes);
	switch_files(cmds_cpy, nb_cmds, pfd);
	close_files(cmds, pfd);
	if (cmds->is_builtin)
		launch_builtin(cmds->cpy);
	else if (path)
	{
		execve(path, cmds->cmd, env);
		perror(path);
		free(path);
		ret = 126;
	}
	else
	{
		error = ft_strjoin(cmds->cmd[0], " : command not found");
		ft_putendl_fd(error, 2);
		free(error);
		ret = 127;
	}
	//fonction de free
	exit(ret);
}

int	executer(t_cmd *cmds, char *env[])
{
	int		pfd[4];
	int		pid;
	int		status;
	int		nb_cmds;
	t_cmd	*cmds_cpy;

	if (open_files(cmds))
		return (close_files(cmds), 1);
	cmds_cpy = cmds;
	nb_cmds = 0;
	if (cmds->is_builtin && !cmds->next)
		return (launch_builtin(cmds));
	pathes = find_pathes(env);
	while (cmds_cpy && ++nb_cmds)
	{
		if (open_pipe(pfd, nb_cmds, cmds->cpy->next))
			return (129);
		pid = try_fork();
		if (pid < 0)
			return (254);
		if (pid == 0)
			launch_cmd(cmds, cmds->cpy, pathes, pfd);
		cmds_cpy = cmds_cpy->next;
	}
	close_files(cmds, pfd);
	while (nb_cmds--)
		wait(-1, &status, 0);
	return (check_status(status));
}
