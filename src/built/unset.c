/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/09/29 11:37:21 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_key(char **env, int key_pos)
{
	char	**env_kv;
	char	*key;
	int		i;

	i = 0;
	env_kv = ft_split(env[key_pos], '=');
	if (env_kv[0])
		key = ft_strdup(env_kv[0]);
	while (env_kv[i])
	{
		free(env_kv[i]);
		i++;
	}
	free(env_kv);
	return (key);
}

int	ft_unset(t_cmd *cmds, char ***env)
{
	char	*var_to_del;
	char	**new_env;
	int		env_size;
	int		i;
	char	*key;

	if (!cmds->cmd[1])
		return (1);
	var_to_del = cmds->cmd[1];
	env_size = get_env_size(*env);
	i = 0;
	new_env = ft_calloc(env_size + 1, sizeof(char *));
	if (!new_env)
		return (-1);
	key = NULL;
	while (i < env_size)
	{
		key = get_env_key(*env, i);
		if (ft_strncmp(key, var_to_del, ft_strlen(key)))
			new_env[i] = ft_strdup((*env)[i]);
		if (key)
			free(key);
		i++;
	}
	i = 0;
	while (i < env_size)
	{
		if ((*env)[i])
			free((*env)[i]);
		i++;
	}
	free(*env);
	*env = new_env;
	return (-1);
}
