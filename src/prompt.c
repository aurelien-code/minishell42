/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:03:43 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/05 23:33:49 by aagathe          ###   ########.fr       */
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
	if (*line != '\0')
		add_history(line);
	return (line);
}
