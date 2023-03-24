/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:18:06 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/24 04:51:12 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_triple_redirects(t_tokens *tokens, int idx, int do_print)
{
	int	i;

	i = 2;
	if (tokens[idx + 1] && tokens[idx + 2])
	{
		if (tokens[idx + 1] == LESS || tokens[idx + 1] == GREAT)
		{
			if (tokens[idx + 2] == LESS || tokens[idx + 2] == GREAT)
			{
				if (do_print)
					printf("%s\n", REDIR_SYNTAX_ERR);
				while (tokens[idx + i] == LESS || tokens[idx + i] == GREAT)
					i++;
				return (i);
			}
		}
	}
	return (0);
}

void	convert_str_builtin(t_line **line)
{
	const char	*builtins[7] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit"};
	int			i;
	t_line		*tmp;

	tmp = (*line);
	while (*line)
	{
		i = 0;
		if ((*line)->type > 0 && (*line)->type == STR)
		{
			while (i < 7)
			{
				if ((*line)->value && !ft_strncmp(builtins[i], \
					(*line)->value, ft_strlen((*line)->value)))
				{
					(*line)->type = BUILTIN;
					break ;
				}
				i++;
			}
		}
		*line = (*line)->next;
	}
	*line = tmp;
}
