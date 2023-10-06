/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/10/06 21:29:59 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option(char *arg)
{
	char	*err;
	char	*err2;

	if (!arg)
		return (0);
	if (*arg++ != '-')
		return (0);
	if (!*arg)
		return (0);
	err = ft_strnjoin("minishell: cd: -", arg, 1);
	err2 = ft_strjoin(err, " : invalid option\n");
	free(err);
	ft_putstr_fd(err2, 2);
	free(err2);
	return (1);
}

void	change_pwd(char *env[])
{
	char	*pwd;
	char	buf[4096];

	while (*env && ft_strncmp("PWD", *env, 3))
		env++;
	if (*env)
	{
		if (getcwd(buf, sizeof(buf)) == NULL)
			return ;
		pwd = ft_strdup(buf);
		if (!pwd)
			return (perror("minishell: malloc"));
		free(*env);
		*env = pwd;
	}
}

static void	print_err_cd(char *path)
{
	char	*err;

	err = ft_strjoin("minishell: cd: ", path);
	perror(err);
	free(err);
}

int	ft_cd(t_cmd *cmds, char *env[])
{
	char	*path;

	if (is_option(cmds->cmd[1]))
		return (2);
	if (!cmds->cmd[1])
	{
		path = getenv("HOME");
		if (!path)
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	}
	else
		path = cmds->cmd[1];
	if (cmds->cmd[1] && cmds->cmd[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (chdir(path) != 0)
	{
		print_err_cd(path);
		return (1);
	}
	change_pwd(env);
	return (0);
}
