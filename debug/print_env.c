/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypages <ypages@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:02:08 by ypages            #+#    #+#             */
/*   Updated: 2023/02/27 11:27:28 by ypages           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_env(char **envp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (envp[i] &&  envp[i][j])
	{
		while (envp[i][j])
		{
			printf("%c", envp[i][j]);
//			if(envp[i][j] == ':')
//				printf("\n");
			j++;
		}
		printf("\n");
		i++;
	}
}
