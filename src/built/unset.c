/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/04/29 10:53:29 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_unset(t_env *env, char *var)
{
	int	var_line;

	var_line = search_var(env, var);
	if (var_line >= 0)
	{
		env = delete_item(env, var);
		if (!env)
			return (NULL);
	}
	else
		return (env);
	return (env);
}
