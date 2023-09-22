/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 19:48:30 by aagathe           #+#    #+#             */
/*   Updated: 2022/05/08 11:57:53 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*m;
	const size_t	m_size = nmemb * size;

	if (nmemb && m_size / nmemb != size)
		return (NULL);
	m = malloc(m_size);
	if (!m)
		return (NULL);
	return (ft_memset(m, 0, m_size));
}
