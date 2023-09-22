/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 17:46:01 by aagathe           #+#    #+#             */
/*   Updated: 2022/05/06 16:10:23 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const size_t	len_s = ft_strlen(src);

	if (len_s < size)
		size = len_s + 1;
	if (size)
	{
		dst = ft_memcpy(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (len_s);
}
