/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:59:35 by aumarin           #+#    #+#             */
/*   Updated: 2023/02/21 18:21:43 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_char(char c)
{
	const char	special_chars[6] = {'<', '>', '|', '\'', '"', '$'};
	int			i;

	i = 0;
	while (i < 6)
	{
		if (c == special_chars[i])
			return (1);
		i++;
	}
	return (0);
}

t_operators	parse_redirect_op(t_line *idx)
{
	if (idx->c == '<')
	{
		if (!idx->prev && idx->next && idx->next->c == '<')
			return (DOUBLE_L_REDIRECT);
		else if (!idx->next && idx->prev && idx->prev->c == '<')
			return (DOUBLE_L_REDIRECT);
		else if (idx->next && idx->prev && \
			(idx->prev->c == '<' || idx->next->c == '<'))
			return (DOUBLE_L_REDIRECT);
		else
			return (SINGLE_L_REDIRECT);
	}
	else if (idx->c == '>')
	{
		if (!idx->prev && idx->next && idx->next->c == '>')
			return (DOUBLE_R_REDIRECT);
		else if (!idx->next && idx->prev && idx->prev->c == '>')
			return (DOUBLE_R_REDIRECT);
		else if (idx->next && idx->prev && \
			(idx->prev->c == '>' || idx->next->c == '>'))
			return (DOUBLE_R_REDIRECT);
		else
			return (SINGLE_R_REDIRECT);
	}
	return (OTHER);
}

t_operators	parse_single_op(t_line *idx, t_operators op)
{
	if (idx->c)
	{
		if (!idx->prev && idx->next && idx->next->c == idx->c)
			return (OTHER);
		else if (!idx->next && idx->prev && idx->prev->c == idx->c)
			return (OTHER);
		else if (idx->next && idx->prev && \
			(idx->prev->c == idx->c || idx->next->c == idx->c))
			return (OTHER);
		else
			return (op);
	}
	else
		return (ERROR);
}

t_operators	parse_operators(t_line *idx)
{
	if (idx->c == '<' || idx->c == '>')
		return (parse_redirect_op(idx));
	else if (idx->c == '|')
		return (parse_single_op(idx, PIPE));
	else if (idx->c == '$')
		return (parse_single_op(idx, ENV_VAR));
	return (OTHER);
}

void	parse_line(t_line *line)
{
	if (!line)
		return ;
	while (line)
	{
		if (is_special_char(line->c))
		{
			print_operator(parse_operators(line));
			printf("\n");
		}
		line = line->next;
	}
}
