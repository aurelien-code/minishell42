/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:45:06 by ypages            #+#    #+#             */
/*   Updated: 2023/03/27 00:44:08 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_checker(t_env *env)
{
	(void)env;
	return (OK);
}

int	ft_exec(t_env *env)
{
	if (exec_checker(env) == OK)
		return (printf("RUN COMMAND\n"), OK);
	return (NOK);
}
