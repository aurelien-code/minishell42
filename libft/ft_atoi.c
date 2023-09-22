/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 17:54:34 by aagathe           #+#    #+#             */
/*   Updated: 2022/04/26 19:30:04 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	neg;
	int	result;

	neg = -1;
	result = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if ((*nptr == '+' || *nptr == '-') && *nptr++ == '-')
		neg = 1;
	while (ft_isdigit(*nptr))
		result = (result * 10) - (*nptr++ - '0');
	return (result * neg);
}
