/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 04:22:34 by ypages            #+#    #+#             */
/*   Updated: 2023/10/02 12:12:44 by aumarin          ###   ########.fr       */
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
