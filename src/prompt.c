/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:03:43 by aumarin           #+#    #+#             */
/*   Updated: 2023/04/26 17:20:52 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_prompt(void)
{
	static char	*line = NULL;

	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline(PROMPT_NAME);
	if (!line)
		return (NULL);
	add_history(line);
	return (line);
}
