/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/10/04 14:11:59 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_key(char **env, int key_pos)
{
	char	**env_kv;
	char	*key;

	key = NULL;
	env_kv = ft_split(env[key_pos], '=');
	if (env_kv[0])
		key = ft_strdup(env_kv[0]);
	ft_free_split(env_kv);
	return (key);
}

char	**build_new_env(char **env, char *var_to_del)
{
	int		env_size;
	int		i;
	int		j;
	char	*key;
	char	**new_env;

	key = NULL;
	i = 0;
	j = 0;
	env_size = get_env_size(env);
	new_env = ft_calloc(env_size + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	while (i < env_size)
	{
		key = get_env_key(env, i);
		if (ft_strncmp(key, var_to_del, ft_strlen(key)))
			new_env[j++] = ft_strdup(env[i]);
		if (key)
			free(key);
		i++;
	}
	return (new_env);
}

int	is_in_new_env(char **new_env, char *str)
{
	int	j;

	j = 0;
	while (new_env[j])
	{
		if (str == new_env[j])
			return (1);
		j++;
	}
	return (0);
}

void	free_env(char ***env, char **new_env)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (!is_in_new_env(new_env, (*env)[i]))
			free((*env)[i]);
		i++;
	}
	free(*env);
}

int	ft_unset(t_cmd *cmds, char ***env)
{
	char	*var_to_del;
	char	**new_env;
	int		i;

	i = 0;
	if (!cmds->cmd[1])
		return (0);
	while (cmds->cmd[i])
	{
		var_to_del = cmds->cmd[i];
		new_env = build_new_env(*env, var_to_del);
		free_env(env, new_env);
		*env = new_env;
		i++;
	}
	return (0);
}
