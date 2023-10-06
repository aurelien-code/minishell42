/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 04:22:34 by ypages            #+#    #+#             */
/*   Updated: 2023/10/06 19:13:00 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_size(char **env)
{
	int	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

void	ft_free_split(char **list)
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

void	ft_free_cpy_env(char **cpy_env)
{
	int	i;

	i = 0;
	while (cpy_env[i])
	{
		free(cpy_env[i]);
		i++;
	}
	free(cpy_env);
}

void	replace_env(char ***env, char **new_env)
{
	int	i;

	i = 0;
	while (i < get_env_size(*env))
	{
		if ((*env)[i])
			free((*env)[i]);
		i++;
	}
	free(*env);
	*env = new_env;
}

int	is_builtin(t_tokens	*tokens)
{
	char	*str;

	str = tokens->value;
	if (!str)
		return (0);
	if (!ft_strncmp(str, "echo", 5))
		return (1);
	else if (!ft_strncmp(str, "cd", 3))
		return (2);
	else if (!ft_strncmp(str, "env", 4))
		return (3);
	else if (!ft_strncmp(str, "export", 7))
		return (4);
	else if (!ft_strncmp(str, "pwd", 4))
		return (5);
	else if (!ft_strncmp(str, "unset", 6))
		return (6);
	else if (!ft_strncmp(str, "exit", 5))
		return (7);
	else
		return (0);
}
