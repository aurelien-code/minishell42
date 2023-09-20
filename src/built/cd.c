/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/09/20 17:50:29 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_cmd *cmds)
{
	(void)cmds;
	/*char	*a_path;

	if (!path)
	{
		if (!getenv("HOME"))
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
		else
			path = getenv("HOME");
	}
	if (chdir(path) < 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (NULL);
	}
	a_path = getcwd(NULL, 0);
	*env = modify_item(*env, "PWD", getcwd(NULL, 0));
	return (a_path);*/
	return (0);
}
