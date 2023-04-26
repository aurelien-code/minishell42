/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:22:47 by aumarin           #+#    #+#             */
/*   Updated: 2023/04/25 19:51:40 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_operator(t_operators op)
{
	if (op == SINGLE_L_REDIRECT)
		printf("SINGLE_L_REDIRECT");
	else if (op == SINGLE_R_REDIRECT)
		printf("SINGLE_R_REDIRECT");
	else if (op == DOUBLE_L_REDIRECT)
		printf("DOUBLE_L_REDIRECT");
	else if (op == DOUBLE_R_REDIRECT)
		printf("DOUBLE_R_REDIRECT");
	else if (op == PIPE_)
		printf("PIPE");
	else if (op == ENV_VAR)
		printf("ENV_VAR");
	else if (op == STR)
		printf("STR");
	else if (op == FILE_)
		printf("FILE");
	else if (op == BUILTIN)
		printf("BUILTIN");
	else
		printf("ERROR");
}

void	print_tokens(t_tokens *tk)
{
	int	i;

	i = 0;
	while (tk[i])
	{
		if (tk[i] == LESS)
			printf("<");
		else if (tk[i] == GREAT)
			printf(">");
		else if (tk[i] == PIPE)
			printf("|");
		else if (tk[i] == QUOTE)
			printf("'");
		else if (tk[i] == DOUBLE_QUOTE)
			printf("\"");
		else if (tk[i] == DOLLAR)
			printf("$");
		else if (tk[i] == SPC)
			printf("space");
		else
			printf("char");
		printf("\n");
		i++;
	}
}

void	print_line(t_line *line)
{
	while (line)
	{
		printf("[Val]: %s	||	[Type]: %d\n", line->value, line->type);
		line = line->next;
	}
}
