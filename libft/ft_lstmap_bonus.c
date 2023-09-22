/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 19:57:17 by aagathe           #+#    #+#             */
/*   Updated: 2022/04/16 19:58:51 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin;
	t_list	*new;
	t_list	*previous;

	begin = NULL;
	while (lst)
	{
		previous = new;
		new = ft_lstnew((*f)(lst->content));
		if (!new)
		{
			ft_lstclear(&begin, del);
			return (NULL);
		}
		if (begin)
			previous->next = new;
		else
			begin = new;
		lst = lst->next;
	}
	return (begin);
}
