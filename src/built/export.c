/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/04/29 10:23:37 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_var(t_env *env, char *var)
{
	char	**name_value;

	name_value = ft_split(var, '=');
	if (!name_value)
		return ;
	env = add_item(env, name_value[0], name_value[1]);
}

void	modify_var(t_env *env, char *var)
{
	char	**name_value;

	name_value = ft_split(var, '=');
	if (!name_value)
		return ;
	env = modify_item(env, name_value[0], name_value[1]);
}

t_env	*ft_export(t_env *env, char *var)
{
	int	var_line;

	var_line = search_var(env, var);
	if (var_line >= 0)
	{
		modify_var(env, var);
		if (!env)
			return (NULL);
	}
	else
	{
		add_var(env, var);
		if (!env)
			return (NULL);
	}
	return (env);
}
