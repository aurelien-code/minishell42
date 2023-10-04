/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/10/04 10:08:32 by aumarin          ###   ########.fr       */
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
	ft_putstr_fd("minishell: pwd: -", 2);
	ft_putchar_fd(*arg, 2);
	ft_putendl_fd(" : invalid option", 2);
	return (1);
}

static int	memory_err(void)
{
	perror("minishell: pwd: write error");
	return (1);
}

int	ft_pwd(t_cmd *cmds)
{
	char	buf[4096];
	size_t	count;
	size_t	size;

	if (is_option(cmds->cmd[1]))
		return (2);
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		perror("pwd");
		return (1);
	}
	size = ft_strlen(buf);
	count = write(1, buf, size);
	if (count != size)
		return (memory_err());
	count = write(1, "\n", 1);
	if (count != 1)
		return (memory_err());
	return (0);
}
