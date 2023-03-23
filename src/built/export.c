/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypages <ypages@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/03/23 04:29:09 by ypages           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_var(char **env, char *var, char *val)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = NULL;
	var = ft_strjoin(var, "=");
	var = ft_strjoin(var, val);
	while (env[i])
		i++;
	new_env = ft_calloc(i + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = var;
	return (new_env);
}

char	**ft_export(char **env, char *var, char *val)
{
	int	var_line;

	var_line = search_var(env, var);
	if (var_line >= 0)
		env[var_line] = ft_strjoin(ft_strjoin(var, "="), val);
	else
		return (add_var(env, var, val));
	return (env);
}
