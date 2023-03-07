/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypages <ypages@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:02:08 by ypages            #+#    #+#             */
/*   Updated: 2023/03/07 11:44:51 by Yoann Pages      ###   ########.fr       */
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
/*
void	print_list(t_env *list)
{
	int i;

	i = 0;
	while (list)
	{
		printf(" %s ", list->name);
		while(list->value[i])
			printf(" %s ", list->value[i++]);
		list = list->next;
	}
}
*/
