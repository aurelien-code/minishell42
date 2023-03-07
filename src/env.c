/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypages <ypages@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:36:50 by ypages            #+#    #+#             */
/*   Updated: 2023/03/06 21:56:48 by Yoann Pages      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

t_env *check_env_path(char **envp)
{
	t_env *env;

	env = malloc(sizeof(t_env));
	env->content = envp ;
	if (!env->content || !env->content[0] || !env->content[0][0])
	{
		env->status = NOK;
		return (printf("[ Error ] - Environment is empty\n"), env);
	}
	else if (env->content[0] && env->content[0][0]
	/*	|| find_exec() == ERROR 
		|| exec() == ERROR */)
		return (env->status = OK, env);
	return (env);
}
