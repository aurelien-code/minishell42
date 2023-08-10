/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:18:06 by aumarin           #+#    #+#             */
/*   Updated: 2023/06/07 18:16:09 by aumarin          ###   ########.fr       */
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

char	*t_operators_to_string(t_operators op)
{
	if (op == ENV_VAR)
		return ("ENV_VAR");
	else if (op == STR)
		return ("STR");
	else if (op == FILE_)
		return ("FILE_");
	else if (op == BUILTIN)
		return ("GREAT");
	else if (op == DOUBLE_R_REDIRECT)
		return ("DOUBLE_R_REDIRECT");
	else if (op == DOUBLE_L_REDIRECT)
		return ("DOUBLE_L_REDIRECT");
	else if (op == SINGLE_R_REDIRECT)
		return ("SINGLE_R_REDIRECT");
	else if (op == SINGLE_L_REDIRECT)
		return ("SINGLE_L_REDIRECT");
	else if (op == PIPE_)
		return ("PIPE_");
	else
		return (NULL);
}

t_operators	string_to_t_operators(char *str)
{
	if (ft_strncmp(str, "ENV_VAR", 7) == 0)
		return (ENV_VAR);
	else if (ft_strncmp(str, "STR", 3) == 0)
		return (STR);
	else if (ft_strncmp(str, "FILE_", 5) == 0)
		return (FILE_);
	else if (ft_strncmp(str, "BUILTIN", 7) == 0)
		return (BUILTIN);
	else if (ft_strncmp(str, "DOUBLE_R_REDIRECT", 17) == 0)
		return (DOUBLE_R_REDIRECT);
	else if (ft_strncmp(str, "DOUBLE_L_REDIRECT", 17) == 0)
		return (DOUBLE_L_REDIRECT);
	else if (ft_strncmp(str, "SINGLE_R_REDIRECT", 17) == 0)
		return (SINGLE_R_REDIRECT);
	else if (ft_strncmp(str, "SINGLE_L_REDIRECT", 17) == 0)
		return (SINGLE_L_REDIRECT);
	else if (ft_strncmp(str, "PIPE_", 5) == 0)
		return (PIPE_);
	else
		return (0);
}
