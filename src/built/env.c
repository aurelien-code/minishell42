/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:02:08 by ypages            #+#    #+#             */
/*   Updated: 2023/10/06 21:18:05 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_env(char *s1, char *s2, char *s3)
{
	char	*err;
	char	*err2;

	err = ft_strjoin(s1, s2);
	err2 = ft_strjoin(err, s3);
	free(err);
	ft_putstr_fd(err2, 2);
	free(err2);
}

static void	print_error_env2(char *arg)
{
	char	*err;
	char	*err2;

	err = ft_strnjoin("env: invalid option -- '", arg, 1);
	err2 = ft_strjoin(err, "\'\n");
	free(err);
	ft_putstr_fd(err2, 2);
	free(err2);
}
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
		print_error_env("env: unrecognized option '--", arg, "\'\n");
	}
	else
		print_error_env2(arg);
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
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
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
