/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypages <ypages@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/03/23 04:29:31 by ypages           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**del_var(char **env, int var_line)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = NULL;
	while (env[i])
		i++;
	new_env = ft_calloc(i - 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (i != var_line)
			new_env[i] = env[i];
		i++;
	}
	return (new_env);
}

char	**ft_unset(char **env, char *var)
{
	int	var_line;

	var_line = search_var(env, var);
	if (var_line >= 0)
		env = del_var(env, var_line);
	return (env);
}
