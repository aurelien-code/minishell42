/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:45:01 by aumarin           #+#    #+#             */
/*   Updated: 2023/04/26 07:01:22 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line	*expand_env_var(t_line **line)
{
	t_line	*tmp;
	char	*env_val;

	env_val = NULL;
	if (!(*line))
		return (NULL);
	tmp = (*line);
	while ((*line))
	{
		if ((*line)->type == ENV_VAR)
		{
			env_val = getenv((*line)->value + 1);
			if (env_val)
				(*line)->value = env_val;
			(*line)->type = STR;
		}
		(*line) = (*line)->next;
	}
	(*line) = tmp;
	return ((*line));
}
