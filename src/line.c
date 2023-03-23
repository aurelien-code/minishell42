/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:02:15 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/22 21:14:08 by ypages           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line	*new_line(void)
{
	t_line	*line;

	line = ft_calloc(1, sizeof(t_line));
	if (!line)
		return (NULL);
	return (line);
}

t_line	*last_line_item(t_line *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_line	*new_line_item(t_line **head, t_operators type, char *value)
{
	t_line	*item;

	if (!type)
		return (NULL);
	item = ft_calloc(1, sizeof(t_line));
	if (!item)
		return (NULL);
	item->type = type;
	item->value = value;
	if (*head)
	{
		if (last_line_item(*head))
			last_line_item(*head)->next = item;
		else
			(*head)->next = item;
	}
	else
		(*head) = item;
	return (*head);
}
