/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:17:57 by aagathe           #+#    #+#             */
/*   Updated: 2022/04/27 03:19:23 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	len_n;

	if (!s)
		return (NULL);
	len_n = ft_strlen(s);
	if (len_n < start)
		len_n = 0;
	else
		len_n -= start;
	if (len > len_n)
		len = len_n;
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	new[len] = '\0';
	return (ft_memcpy(new, s + start, len));
}
