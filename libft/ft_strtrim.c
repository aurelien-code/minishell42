/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:24:35 by aagathe           #+#    #+#             */
/*   Updated: 2022/04/27 03:18:51 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	char	*str;

	if (!(s1 && set))
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size = ft_strlen(s1);
	while (size && ft_strchr(set, s1[size - 1]))
		size--;
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[size] = '\0';
	return (ft_memcpy(str, s1, size));
}
