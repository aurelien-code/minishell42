/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/10/04 01:15:52 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option(char *arg)
{
	if (!arg)
		return (0);
	if (*arg++ != '-')
		return (0);
	if (!*arg)
		return (0);
	ft_putstr_fd("minishell: cd: -", 2);
	ft_putchar_fd(*arg, 2);
	ft_putendl_fd(" : invalid option", 2);
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
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		return (1);
	}
	change_pwd(env);
	return (0);
}
