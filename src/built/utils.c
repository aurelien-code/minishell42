/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 04:22:34 by ypages            #+#    #+#             */
/*   Updated: 2023/05/03 16:33:12 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_var(t_env *env, char *var)
{
	char	**name_value;

	name_value = ft_split(var, '=');
	if (!name_value)
		return (-1);
	while (env)
	{
		if (!ft_strncmp(env->name, name_value[0], ft_strlen(name_value[0])))
			return (1);
		env = env->next;
	}
	return (-1);
}
