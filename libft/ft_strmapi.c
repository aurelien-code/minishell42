/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:22:27 by aagathe           #+#    #+#             */
/*   Updated: 2022/04/16 18:24:03 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	size;
	char			*new;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	new = malloc((size + 1) * sizeof(char));
	if (!new)
		return (NULL);
	new[size] = '\0';
	while (size--)
		new[size] = (*f)(size, s[size]);
	return (new);
}
