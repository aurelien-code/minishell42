/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypages <ypages@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:02:08 by ypages            #+#    #+#             */
/*   Updated: 2023/03/22 20:35:56 by ypages           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i] && envp[i][j])
	{
		while (envp[i][j])
		{
			printf("%c", envp[i][j]);
			j++;
		}
		printf("\n");
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
			printf("%s\n", envp[i]);
		i++;
	}
}
