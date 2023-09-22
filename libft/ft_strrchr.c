/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:23:31 by aagathe           #+#    #+#             */
/*   Updated: 2022/04/16 19:35:48 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	size;

	c = (unsigned char)c;
	size = ft_strlen(s) + 1;
	while (size--)
		if (s[size] == c)
			return ((char *)s + size);
	return (NULL);
}
