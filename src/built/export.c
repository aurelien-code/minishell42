/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/09/28 17:14:26 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_new_env_var(char **env, char *new_var)
{
	int		env_size;
	int		i;
	char	**new_env;

	env_size = 0;
	i = 0;
	while(env[env_size])
		env_size++;
	new_env = ft_calloc(env_size + 2, sizeof(char *));
	if (!new_env)
		return (NULL);
	while (i < env_size)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	return(new_env); 
}

int	get_env_size(char **env)
{
	int size;

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
	return (ret_value);
}

void dbg_print_env(char **env);

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
	*env = new_env;
	return (126);
}
