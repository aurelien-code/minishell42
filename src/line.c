/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:02:15 by aumarin           #+#    #+#             */
/*   Updated: 2023/02/21 17:02:40 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line	*get_first(t_line *line)
{
	if (!line)
		return (NULL);
	if (line && !line->prev)
		return (line);
	while (line->prev)
	{
		line = line->prev;
	}
	return (line);
}

t_line	*create_line(char *str)
{
	t_line	*current;
	t_line	*tmp;

	current = NULL;
	while (*str)
	{
		tmp = ft_calloc(1, sizeof(t_line));
		if (!tmp)
			return (NULL);
		tmp->prev = current;
		tmp->next = NULL;
		tmp->c = *str;
		if (!current)
			current = tmp;
		else
		{
			current->next = tmp;
			current = current->next;
		}
		str++;
	}
	return (get_first(current));
}
