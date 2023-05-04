/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:30:11 by aumarin           #+#    #+#             */
/*   Updated: 2023/05/04 15:20:49 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	t_tokens	*tokens;
	char		*str_line;
	t_line		*line_parsed;
	t_env		*ll_env;

	(void)argv;
	if (!envp || argc > 1)
		return (1);
	sig_init();
	ll_env = convert_env(envp);
	str_line = NULL;
	while (1)
	{
		str_line = ft_prompt();
		if (str_line)
		{
			tokens = lexer(str_line);
			line_parsed = parse(str_line, tokens);
			ll_env = ft_exec(line_parsed, ll_env);
		}
		else
			sig_ctrl_d();
	}
	rl_clear_history();
	return (0);
}
