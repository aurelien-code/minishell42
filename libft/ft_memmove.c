/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 19:16:33 by aagathe           #+#    #+#             */
/*   Updated: 2022/04/26 19:49:37 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s = src;

	if (!dest && !src)
		return (NULL);
	d = dest;
	if (d < s)
		return (ft_memcpy(dest, src, n));
	else
		while (n--)
			d[n] = s[n];
	return (dest);
}
