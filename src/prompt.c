/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:03:43 by aumarin           #+#    #+#             */
/*   Updated: 2023/02/21 17:02:33 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line	*ft_prompt(void)
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
	return (create_line(line));
}
