/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:02:15 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/20 11:56:01 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line	*last_line_item(t_line *head)
{
	if (!head)
		return (NULL);
	while (head)
		head = head->next;
	return (head);
}

t_line	*new_line_item(t_line *head, t_operators type, char *value)
{
	t_line	*item;

	if (!type || !value)
		return (NULL);
	item = ft_calloc(1, sizeof(t_line));
	if (!item)
		return (NULL);
	if (last_line_item(head))
	{
		item->type = type;
		item->value = value;
		last_line_item(head)->next = item;
	}
	if (!head)
		head = item;
	return (item);
}

t_line	*new_line(void)
{
	t_line	*line;

	line = ft_calloc(1, sizeof(t_line));
	if (!line)
		return (NULL);
	return (line);
}
