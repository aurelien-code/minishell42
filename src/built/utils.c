/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 04:22:34 by ypages            #+#    #+#             */
/*   Updated: 2023/04/26 16:19:44 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_var(char **env, char *var)
{
	int		i;
	char	*var_name;

	if (!var || !env)
		return (-1);
	if (!ft_strchr(var, '='))
		return (-1);
	var_name = NULL;
	i = 0;
	var_name = ft_split(&var[i], '=')[0];
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(ft_split(env[i], '=')[0]) + 1))
			return (i);
		i++;
	}
	return (-1);
}
