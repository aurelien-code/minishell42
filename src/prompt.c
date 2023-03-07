/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:03:43 by aumarin           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/01 14:06:29 by ypages           ###   ########.fr       */
=======
/*   Updated: 2023/03/07 12:05:29 by aumarin          ###   ########.fr       */
>>>>>>> ff43190 (add: lexer)
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
