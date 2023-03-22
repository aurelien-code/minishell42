/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypages <ypages@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:36:50 by ypages            #+#    #+#             */
/*   Updated: 2023/03/22 17:54:42 by ypages           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_env *check_env_path(char **envp)
{
	t_env *env;
	int i;
	int j;

	env = malloc(sizeof(t_env));
	env->content = envp ;
	i = 0;
	j = 0;
	if (!env->content || !env->content[0] || !env->content[0][0])
	{
		env->status = NOK;
		return (env);
	}
	else if (env->content[0] && env->content[0][0])
		return (env->status = OK, env);
	return (env);
}
