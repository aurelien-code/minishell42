/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypages <ypages@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 04:22:34 by ypages            #+#    #+#             */
/*   Updated: 2023/03/23 04:22:57 by ypages           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_var(char **env, char *var)
{
	int	line_nbr;

	line_nbr = 0;
	while (env[line_nbr])
	{
		if (!(ft_strncmp(var, env[line_nbr], ft_strlen(var))) \
				&& env[line_nbr][ft_strlen(var)] == '=')
			return (line_nbr);
		line_nbr++;
	}
	return (-1);
}
