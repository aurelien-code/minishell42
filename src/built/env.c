/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:02:08 by ypages            #+#    #+#             */
/*   Updated: 2023/05/03 16:19:31 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env)
{
	if (!env || !env->name)
		return ;
	while (env)
	{
		if (env && env->value && env->name)
			printf("%s=%s\n", env->name, env->value);
		else if (env->name && !env->value)
			printf("%s=\n", env->name);
		else
			return ;
		env = env->next;
	}
}
