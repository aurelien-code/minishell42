/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:33:45 by aagathe           #+#    #+#             */
/*   Updated: 2023/10/03 06:39:50 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*go_to_cmds(t_cmd *cmds, int nb_cmds)
{
	while (--nb_cmds)
		cmds = cmds->next;
	return (cmds);
}

int	is_path(char *cmd)
{
	if (*cmd != '/' && ft_strncmp(cmd, "./", 2) && ft_strncmp(cmd, "../", 3))
		return (0);
	return (1);
}

char	*check_path(char *cmd, char **pathes)
{
	char	*ret;
	char	*path;
	char	*slash;

	ret = NULL;
	if (ft_strlen(cmd) && !is_path(cmd))
	{
		while (*pathes)
		{
			slash = ft_strjoin(*pathes++, "/");
			path = ft_strjoin(slash, cmd);
			free(slash);
			if (!access(path, X_OK))
				return (path);
			if (!access(path, F_OK))
			{
				free(ret);
				ret = ft_strdup(path);
			}
			free(path);
		}
	}
	else
		ret = ft_strdup(cmd);
	return (ret);
}

char	**find_pathes(char *env[])
{
	while (*env && ft_strncmp(*env, "PATH", 4))
		env++;
	return (ft_split(*env + 5, ':'));
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

void	free_pathes(char **pathes)
{
	int	i;

	i = 0;
	while ((pathes[i]))
		free(pathes[i++]);
	free(pathes);
	return ;
}
