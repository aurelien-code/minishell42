/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:30:11 by aumarin           #+#    #+#             */
/*   Updated: 2023/04/26 09:21:14 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tokens	*tokens;
	char		*str_line;
	t_line		*line_parsed;

	if (!envp || argc > 1)
		return (1);
	(void)argv;
	while (1)
	{
		str_line = ft_prompt();
		tokens = lexer(str_line);
		line_parsed = parse(str_line, tokens);
		//print_line(line_parsed);
		ft_exec(line_parsed);
	}
	rl_clear_history();
	return (0);
}
