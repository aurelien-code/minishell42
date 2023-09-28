/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/09/28 15:14:51 by aagathe          ###   ########.fr       */
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
	ft_putstr_fd("minishell: ft_cd: -", 2);
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

void	change_oldpwd(char *env[], char *oldpwd)
{
	change_pwd(env);
	while (*env && ft_strncmp("OLDPWD", *env, 6))
		env++;
	if (*env)
	{
		free(*env);
		*env = oldpwd;
	}
	//else
		// ft_export(oldpwd);
}

char	*get_oldpwd(void)
{
	char	*pwd;
	char	buf[4096];

	if (getcwd(buf, sizeof(buf)) == NULL)
		return (NULL);
	pwd = ft_strdup(buf);
	if (!pwd)
		perror("minishell: malloc");
	return (pwd);
}

int	ft_cd(t_cmd *cmds, char *env[])
{
	char	*path;
	char	*oldpwd;

	if (is_option(cmds->cmd[1]))
		return (2);
	if (!cmds->cmd[1])
	{
		path = getenv("HOME");
		if (!path)
			return (ft_putstr_fd("ft_cd: HOME not set\n", 2), 1);
	}
	else
		path = cmds->cmd[1];
	if (cmds->cmd[1] && cmds->cmd[2])
		return (ft_putendl_fd("minishell: ft_cd: too many arguments", 2), 1);
	oldpwd = get_oldpwd();
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: ft_cd: ", 2);
		perror(path);
		return (1);
	}
	change_oldpwd(env, oldpwd);
	return (0);
}
