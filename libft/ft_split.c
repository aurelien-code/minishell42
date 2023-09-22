/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:57:08 by aagathe           #+#    #+#             */
/*   Updated: 2022/11/27 16:19:16 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_splitup(char const *str, char c, int ct_word, char **list)
{
	int		letter;

	while (ct_word--)
	{
		while (*str == c)
			++str;
		letter = 0;
		while (*str && *str != c && ++str)
			++letter;
		*list = malloc((letter + 1) * sizeof(char));
		if (!*list)
			return (0);
		*list = ft_memcpy(*list, str - letter, letter);
		(*list++)[letter] = '\0';
	}
	*list = NULL;
	return (1);
}

static int	ft_count_word(char const *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
			count++;
		while (*str && *str != c)
			str++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**list;
	int		ct_word;

	if (!s)
		return (NULL);
	ct_word = ft_count_word(s, c);
	list = malloc((ct_word + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	if (!ft_splitup(s, c, ct_word, list))
	{
		i = 0;
		while (list[i])
			free(list[i++]);
		free(list);
		return (NULL);
	}
	return (list);
}
