/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 02:33:44 by aagathe           #+#    #+#             */
/*   Updated: 2022/04/30 18:29:37 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*nbr;
	int		size;
	long	nb;

	nb = n;
	size = 1;
	while ((n > 9 || n < -9) && ++size)
		n /= 10;
	if (nb < 0 && ++size)
		nb = -nb;
	nbr = malloc((size + 1) * sizeof(char));
	if (!nbr)
		return (NULL);
	*nbr = '-';
	nbr[size] = '\0';
	while (nb || !nbr[size])
	{
		nbr[--size] = nb % 10 + '0';
		nb /= 10;
	}
	return (nbr);
}
