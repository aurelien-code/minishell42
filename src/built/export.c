/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/05/04 14:04:35 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_export(t_env *env, char *var)
{
	int		var_line;
	char	**name_value;

	var_line = search_var(env, var);
	if (var_line >= 0)
	{
		name_value = ft_split(var, '=');
		if (!name_value)
			return (NULL);
		env = modify_item(env, name_value[0], name_value[1]);
		if (!env)
			return (NULL);
	}
	else
	{
		name_value = ft_split(var, '=');
		if (!name_value)
			return (NULL);
		env = add_item(env, name_value[0], name_value[1]);
		if (!env)
			return (NULL);
	}
	return (env);
}
