/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/09/26 08:35:39 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *cmds)
{
	char	buf[4096];

	(void)cmds;
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		perror("ft_pwd");
		return (1);
	}
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
