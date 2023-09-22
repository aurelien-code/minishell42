/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 19:20:17 by aagathe           #+#    #+#             */
/*   Updated: 2022/04/30 21:18:59 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && *s2)
		if (n-- && *s1++ != *s2++)
			return ((unsigned char)*--s1 - (unsigned char)*--s2);
	if (n)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}
