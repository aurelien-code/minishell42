/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:02:08 by ypages            #+#    #+#             */
/*   Updated: 2023/10/04 10:30:46 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option(char *arg, char **cmd)
{
	if (!arg)
		return (0);
	if (*arg++ != '-')
		return (0);
	if (!*arg)
		return (0);
	if (*arg == '-' && arg++)
	{
		if (!*arg)
		{
			free(cmd[1]);
			cmd[1] = NULL;
			return (0);
		}
		ft_putstr_fd("env: unrecognized option '--", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("\'", 2);
	}
	else
	{
		ft_putstr_fd("env: invalid option -- '", 2);
		ft_putchar_fd(*arg, 2);
		ft_putendl_fd("\'", 2);
	}
	return (1);
}

static int	memory_err(void)
{
	perror("env: write error");
	return (125);
}

int	ft_env(t_cmd *cmds, char *env[])
{
	int		i;
	size_t	size;
	size_t	count;

	if (is_option(cmds->cmd[1], cmds->cmd))
		return (125);
	if (cmds->cmd[1])
	{
		ft_putendl_fd("minishell: env: too many arguments", 2);
		return (1);
	}
	i = 0;
	while (env[i])
	{
		if (!ft_strchr(env[i], '=') && ++i)
			continue ;
		size = ft_strlen(env[i]);
		count = write(1, env[i++], size);
		if (count != size)
			return (memory_err());
		count = write(1, "\n", 1);
		if (count != 1)
			return (memory_err());
	}
	return (0);
}
