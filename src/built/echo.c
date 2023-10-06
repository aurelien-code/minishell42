/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/10/06 16:54:05 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i + 1])
	{
		j = 0;
		if (args[i + 1][j++] != '-')
			break ;
		while (args[i + 1][j] == 'n')
			j++;
		if (args[i + 1][j])
			break ;
		i++;
	}
	return (i);
}

static int	memory_err(size_t count, size_t n)
{
	if (count == n)
		return (0);
	perror("minishell: echo: write error");
	return (1);
}

int	ft_echo(t_cmd *cmds)
{
	int		i;
	int		opt;
	size_t	count_c;
	size_t	w_size;

	opt = is_option(cmds->cmd);
	i = opt + 1;
	while (cmds->cmd[i])
	{
		if (i != opt + 1)
		{
			count_c = write(1, " ", 1);
			if (memory_err(count_c, 1))
				return (1);
		}
		w_size = ft_strlen(cmds->cmd[i]);
		count_c = write(1, cmds->cmd[i++], w_size);
		if (memory_err(count_c, w_size))
			return (1);
	}
	if (!opt)
		count_c = write(1, "\n", 1);
	if (!opt && memory_err(count_c, 1))
		return (1);
	return (0);
}
