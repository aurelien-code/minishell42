/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:02:08 by ypages            #+#    #+#             */
/*   Updated: 2023/03/23 03:33:10 by ypages           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i] && envp[i][j])
	{
		printf("print --- %d %s\n", i, envp[i]);
		i++;
	}
}

void	print_var(char **envp, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!(ft_strncmp(var, envp[i], ft_strlen(var))) \
				&& envp[i][ft_strlen(var)] == '=')
		{
			printf("print -- <%s>\n", envp[i]);
			j++;
		}
		i++;
	}
	if (j == 0)
		printf("print -- Variable <%s> not found\n", var);
}
