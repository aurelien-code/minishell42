/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:45:01 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/26 22:12:30 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env_var(char **env, char *var)
{
	int	i;

	if (!env || !var)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], ft_strlen(var)))
		{
			if (env[i][ft_strlen(var)] == '=')
				return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	return (NULL);
}
