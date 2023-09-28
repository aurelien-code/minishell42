/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/09/29 01:32:48 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_free_split(char **list)
{
	int	i;

	i = 0;
	if (!list)
		return ;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

int		should_modify(char **env, char *new_var)
{
	int		i;
	char	**var_kv;
	char	**env_kv;
	int		j;

	var_kv = ft_split(new_var, '=');
	if (!var_kv[0])
	{
		ft_free_split(var_kv);
		return (0);
	}
	i = 0;
	while (env[i])
	{
		env_kv = ft_split(env[i], '=');
		if (!ft_strncmp(env_kv[0], var_kv[0], ft_strlen(env_kv[0])))
		{
			ft_free_split(var_kv);
			ft_free_split(env_kv);
			return (i);
		}
		j = 0;
		while (env_kv[j])
		{
			free(env_kv[j]);
			j++;
		}
		free(env_kv);
		i++;
	}
	ft_free_split(var_kv);
	return (-1);
}

char	**add_new_env_var(char **env, char *new_var)
{
	int		env_size;
	int		i;
	char	**new_env;
	int		modify;

	modify = should_modify(env, new_var);
	env_size = 0;
	i = 0;
	while (env[env_size])
		env_size++;
	if (modify < 0)
		new_env = ft_calloc(env_size + 2, sizeof(char *));
	else
		new_env = ft_calloc(env_size + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	while (i < env_size)
	{
		if (i == modify)
			new_env[i] = ft_strdup(new_var);
		else
			new_env[i] = ft_strdup(env[i]);
		i++;
	}
	if (modify < 0)
		new_env[i] = ft_strdup(new_var);
	return (new_env);
}

int	get_env_size(char **env)
{
	int	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

int	ft_export_no_options(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}

int	is_valid_identifier(char *id)
{
	char	**id_split;
	int		ret_value;

	ret_value = 0;
	if (id[0] && ft_isdigit(id[0]))
		return (ret_value);
	id_split = ft_split(id, '=');
	if (id_split[0] && ft_strchr(id_split[0], '-') != NULL)
		ret_value = 0;
	else
		ret_value = 1;
	if (id_split[0])
		free(id_split[0]);
	if (id_split[1])
		free(id_split[1]);
	if (id_split)
		free(id_split);
	return (ret_value);
}

int	ft_export(t_cmd *cmds, char ***env)
{
	char	**new_env;
	int		i;
	int		env_size;

	i = 0;
	if (!cmds->cmd[1] && *env)
		return (ft_export_no_options(*env));
	if (!cmds->cmd[0] || !(*env))
		return (1);
	if (!is_valid_identifier(cmds->cmd[1]))
		return (1);
	env_size = get_env_size(*env);
	new_env = add_new_env_var(*env, cmds->cmd[1]);
	while (i < env_size)
	{
		if ((*env)[i])
			free((*env)[i]);
		i++;
	}
	free(*env);
	*env = new_env;
	return (126);
}
