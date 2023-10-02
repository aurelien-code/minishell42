/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:02:08 by ypages            #+#    #+#             */
/*   Updated: 2023/10/02 18:26:33 by aagathe          ###   ########.fr       */
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
	ft_putstr_fd("minishell: env: -", 2);
	ft_putchar_fd(*arg, 2);
	ft_putendl_fd(" : invalid option", 2);
	return (1);
}

int	ft_env(t_cmd *cmds, char *env[])
{
	int	i;

	if (is_option(cmds->cmd[1]))
		return (2);
	if (cmds->cmd[1])
	{
		ft_putendl_fd("minishell: env: too many arguments", 2);
		return (1);
	}
	i = 0;
	while (env[i])
		ft_putendl_fd(env[i++], 1);
	return (0);
}
