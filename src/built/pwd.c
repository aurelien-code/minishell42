/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/09/28 11:53:02 by aagathe          ###   ########.fr       */
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
	ft_putstr_fd("minishell: ft_pwd: -", 2);
	ft_putchar_fd(*arg, 2);
	ft_putendl_fd(" : invalid option", 2);
	return (1);
}

int	ft_pwd(t_cmd *cmds)
{
	char	buf[4096];

	if (is_option(cmds->cmd[1]))
		return (2);
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		perror("ft_pwd");
		return (1);
	}
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
