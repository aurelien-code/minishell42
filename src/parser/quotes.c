/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:15:39 by aumarin           #+#    #+#             */
/*   Updated: 2023/05/25 17:33:55 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unclosed(t_tokens *tokens, int tmp, t_tokens quote)
{
	if (tokens[tmp] != quote)
	{
		printf("%s\n", UNCLOSE_QUOTE_ERR);
		return (0);
	}
	return (1);
}
