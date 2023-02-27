/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypages <ypages@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:45:06 by ypages            #+#    #+#             */
/*   Updated: 2023/02/27 10:47:36 by ypages           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
int check_env_path(char **argv, char **envp)
{
	return (OK);
}*/
/*
int read_env
int search exec
*/

int ft_exec (int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	if(check_env_path(argv, envp) == OK)
		return (OK);
	else
		return (NOK);
	return (OK);
}
