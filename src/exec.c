/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypages <ypages@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:45:06 by ypages            #+#    #+#             */
/*   Updated: 2023/03/01 15:09:00 by ypages           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exec_checker(t_env *env)
{
	return (OK);
}

int ft_exec (t_env *env)
{
	if(exec_checker(env) == OK )
		return (printf("RUN COMMAND\n"), OK);
	return (NOK);
}
