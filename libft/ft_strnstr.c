/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 19:20:45 by aagathe           #+#    #+#             */
/*   Updated: 2022/04/30 21:58:33 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_l;

	len_l = ft_strlen(little);
	(void)ft_strlen(big);
	if (!len_l)
		return ((char *)big);
	if (len >= len_l)
	{
		len -= len_l - 1;
		while (*big && len--)
			if (!ft_strncmp(big++, little, len_l))
				return ((char *)--big);
	}
	return (NULL);
}
