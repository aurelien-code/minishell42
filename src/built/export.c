/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/09/20 17:53:25 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_cmd *cmds)
{
	(void)cmds;
	/*int		var_line;
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
	return (env);*/
	return (0);
}
