/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:15:42 by aagathe           #+#    #+#             */
/*   Updated: 2022/04/27 03:11:43 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size1;
	size_t	size2;
	char	*str;

	if (!(s1 && s2))
		return (NULL);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	str = malloc((size1 + size2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str = ft_memcpy(str + size1, s2, size2 + 1);
	return (ft_memcpy(str - size1, s1, size1));
}
