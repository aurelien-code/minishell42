/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 17:46:33 by aagathe           #+#    #+#             */
/*   Updated: 2022/05/06 16:07:22 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			i;
	const size_t	len_d = ft_strlen(dst);
	const size_t	len_s = ft_strlen(src);

	if (size <= len_d)
		return (size + len_s);
	i = -1;
	while (++i < len_s && i < size - len_d - 1)
		dst[len_d + i] = src[i];
	dst[len_d + i] = '\0';
	return (len_s + len_d);
}
