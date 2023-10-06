/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/10/06 21:32:24 by aagathe          ###   ########.fr       */
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
	err = ft_strnjoin("minishell: pwd: -", arg, 1);
	err2 = ft_strjoin(err, " : invalid option\n");
	free(err);
	ft_putstr_fd(err2, 2);
	free(err2);
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
