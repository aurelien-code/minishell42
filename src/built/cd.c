/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/09/26 08:36:16 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_cmd *cmds)
{
	char	*path;

	if (!cmds->cmd[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("ft_cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
		path = cmds->cmd[1];
	if (chdir(path) != 0)
	{
		perror("ft_cd");
		return (1);
	}
	return (0);
}
