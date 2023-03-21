/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:59:35 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/21 13:59:47 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_str(char *str_line, t_tokens *tokens, int *idx)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = ft_calloc(2, sizeof(char));
	if (!tmp)
		return ;
	while (tokens[*idx] == CHAR)
	{
		tmp[0] = str_line[*idx];
		str = ft_strjoin(str, tmp);
		(*idx)++;
	}
	printf("str = -> %s\n", str);
	return ;
}

void	parse_quotes(void)
{
	return ;
}

void	parse_redirects(void)
{
	return ;
}

void	parse_env(char *str_line, t_tokens *tokens, int *idx)
{
	int	i;

	i = *idx + 1;
	if (tokens[i] == CHAR)
		parse_str(str_line, tokens, &i);
	*idx = i;
}

t_line	*parse(char *str_line, t_tokens	*tokens)
{
	t_line	*line;
	int		i;

	line = ft_calloc(1, sizeof(t_line));
	if (!line)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		if (tokens[i] == CHAR)
			parse_str(str_line, tokens, &i);
		else if (tokens[i] == QUOTE || tokens[i] == DOUBLE_QUOTE)
			parse_quotes();
		else if (tokens[i] == GREAT || tokens[i] == LESS)
			parse_redirects();
		else if (tokens[i] == DOLLAR)
			parse_env(str_line, tokens, &i);
		i++;
	}
	return (line);
}
