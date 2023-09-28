/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypages <ypages@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/09/27 19:42:53 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option(char *arg)
{
	if (!arg)
		return (0);
	if (*arg++ != '-')
		return (0);
	while (*arg == 'n')
		arg++;
	if (*arg)
		return (0);
	return (1);
}

int	ft_echo(t_cmd *cmds)
{
	int	i;
	int	opt;

	opt = is_option(cmds->cmd[1]);
	i = opt + 1;
	while (cmds->cmd[i])
	{
		if (i != opt + 1)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(cmds->cmd[i++], 1);
	}
	if (!opt)
		ft_putchar_fd('\n', 1);
	return (0);
}
