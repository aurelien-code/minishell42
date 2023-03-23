/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:59:35 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/23 12:18:21 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_str(char *str_line, t_tokens *tokens, int *idx)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = ft_calloc(2, sizeof(char));
	if (!tmp)
		return (NULL);
	while (tokens[*idx] && tokens[*idx] == CHAR)
	{
		tmp[0] = str_line[*idx];
		str = ft_strjoin(str, tmp);
		(*idx)++;
	}
	printf("str -> %s\n", str);
	return (str);
}

void	parse_quotes(void)
{
	return ;
}

void	parse_redirects(t_line **line, t_tokens *tokens, int *idx)
{
	if (parser_triple_redirects(tokens, *idx, 1))
		(*idx) += parser_triple_redirects(tokens, *idx, 0);
	else if (tokens[*idx + 1] == tokens[*idx])
	{
		if (tokens[*idx] == GREAT)
			new_line_item(line, DOUBLE_R_REDIRECT, NULL);
		else if (tokens[*idx] == LESS)
			new_line_item(line, DOUBLE_L_REDIRECT, NULL);
		(*idx)++;
	}
	else
	{
		if (tokens[*idx] == LESS && tokens[*idx + 1] == GREAT)
			printf("%s\n", REDIR_NEWLINE_ERR);
		else if (tokens[*idx] == GREAT && tokens[*idx + 1] == LESS)
			printf("%s\n", REDIR_SYNTAX_ERR);
		else
		{
			if (tokens[*idx] == GREAT)
				new_line_item(line, SINGLE_R_REDIRECT, NULL);
			else
				new_line_item(line, SINGLE_L_REDIRECT, NULL);
		}
	}
}

char	*parse_env(char *str_line, t_tokens *tokens, int *idx)
{
	int		i;
	char	*str;

	str = NULL;
	i = *idx + 1;
	if (tokens[i] == CHAR)
		str = parse_str(str_line, tokens, &i);
	*idx = i;
	return (str);
}

t_line	*parse(char *str_line, t_tokens	*tokens)
{
	t_line		*line;
	int			i;
	char		*x;

	i = 0;
	line = NULL;
	while (tokens[i])
	{
		x = NULL;
		if (tokens[i] == CHAR)
			x = parse_str(str_line, tokens, &i);
		else if (tokens[i] == QUOTE || tokens[i] == DOUBLE_QUOTE)
			parse_quotes();
		else if (tokens[i] == GREAT || tokens[i] == LESS)
			parse_redirects(&line, tokens, &i);
		else if (tokens[i] == DOLLAR)
			x = parse_env(str_line, tokens, &i);
		else if (tokens[i] == PIPE)
			new_line_item(&line, PIPE_, NULL);
		i++;
		if (x != NULL)
			new_line_item(&line, STR, x);
	}
	print_line(line);
	return (line);
}
