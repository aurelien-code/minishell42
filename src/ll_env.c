/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:50:52 by aumarin           #+#    #+#             */
/*   Updated: 2023/04/29 11:04:10 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*build_minimal_env(void)
{
	t_env	*tmp;

	tmp = ft_calloc(1, sizeof(t_env));
	if (!tmp)
		return (NULL);
	tmp->name = ft_strdup("PWD");
	tmp->value = ft_strdup(ft_pwd());
	tmp->next = NULL;
	return (tmp);
}

t_env	*convert_env(char **envp)
{
	t_env	*env;
	t_env	*tmp;
	int		i;
	char	**name_value;

	i = 0;
	env = NULL;
	if (envp[i] == NULL)
		return (build_minimal_env());
	while (envp[i])
	{
		tmp = ft_calloc(1, sizeof(t_env));
		if (!tmp)
			return (NULL);
		name_value = ft_split(envp[i], '=');
		if (!name_value)
			continue ;
		tmp->name = name_value[0];
		tmp->value = name_value[1];
		tmp->next = env;
		env = tmp;
		i++;
	}
	return (env);
}

t_env	*add_item(t_env *env, char *name, char *value)
{
	t_env	*tmp;
	t_env	*first;

	tmp = ft_calloc(1, sizeof(t_env));
	if (!tmp)
		return (NULL);
	tmp->name = name;
	tmp->value = value;
	tmp->next = NULL;
	if (env)
		first = env;
	else
		return (tmp);
	while (env)
	{
		if (!env->next)
		{
			env->next = tmp;
			return (first);
		}
		env = env->next;
	}
	return (first);
}

t_env	*modify_item(t_env *env, char *name, char *value)
{
	t_env	*first;

	if (!env)
		return (NULL);
	first = env;
	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(name)))
		{
			env->value = value;
			return (first);
		}
		env = env->next;
	}
	return (first);
}

t_env	*delete_item(t_env *env, char *name)
{
	t_env	*first;
	t_env	*tmp;

	if (!env)
		return (NULL);
	first = env;
	if (!ft_strncmp(env->name, name, ft_strlen(name)))
	{
		tmp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		return (tmp);
	}
	while (env->next)
	{
		if (!ft_strncmp(env->next->name, name, ft_strlen(name)))
		{
			tmp = env->next->next;
			free(env->next->name);
			free(env->next->value);
			free(env->next);
			env->next = tmp;
			return (first);
		}
		env = env->next;
	}
	return (first);
}
