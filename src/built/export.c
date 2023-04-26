/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/04/26 17:31:30 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_var(char **env, char *var)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(var);
	i = 0;
	while (new_env[i])
	{
		env[i] = new_env[i];
		i++;
	}
}

void	modify_var(char **env, char *var, int idx)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (env[i])
	{
		if (i == idx)
			new_env[i] = ft_strdup(var);
		else
			new_env[i] = ft_strdup(env[i]);
		i++;
	}
	i = 0;
	while (new_env[i])
	{
		env[i] = new_env[i];
		i++;
	}
	free(new_env);
}

char	**ft_export(char **env, char *var)
{
	int	var_line;

	var_line = search_var(env, var);
	if (var_line >= 0)
	{
		printf("Modify var\n");
		modify_var(env, var, var_line);
		if (!env)
			return (NULL);
	}
	else
	{
		printf("Add var\n");
		add_var(env, var);
		if (!env)
			return (NULL);
	}
	return (env);
}
