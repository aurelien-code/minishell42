/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:43:39 by aumarin           #+#    #+#             */
/*   Updated: 2023/08/24 03:54:37 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

char	*expand(t_lexer *lexer_arr, int i)
{
	int		j;

	j = 0;
	if (lexer_arr[i].type != EXPAND)
		return (NULL);
	if (lexer_arr[i + 1].value == '?')
		return (ft_itoa(g_exit_code));
	while (lexer_arr[i + j].value && lexer_arr[i].type == EXPAND)
	{
		j++;
		if (lexer_arr[i + j].value == ' ' || lexer_arr[i + j].value == '\0')
		{
			printf("-> %s\n", getenv(substr_lexer(lexer_arr, i, i + j)));
			return (getenv(substr_lexer(lexer_arr, i, i + j)));
		}
	}
	return (NULL);
}
