/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:09:13 by aagathe           #+#    #+#             */
/*   Updated: 2022/04/16 18:10:01 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*visit;
	t_list	*nxt;

	if (!lst)
		return ;
	visit = *lst;
	while (visit)
	{
		nxt = visit->next;
		ft_lstdelone(visit, del);
		visit = nxt;
	}
	*lst = NULL;
}
