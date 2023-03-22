/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:30:11 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/01 15:07:19 by ypages           ###   ########.fr       */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tokens	*tokens;
	char		*str_line;

	if (!envp || argc > 1)
		return (1);
	(void)argv;
	while (1)
	{
		str_line = ft_prompt();
		tokens = lexer(str_line);
		parse(str_line, tokens);
	}
	t_env *env;
	(void)argv;
	
	env = check_env_path(envp);
	if (argc > 1 || env->status == NOK)
		return (1);
	parse_line(ft_prompt());
	rl_clear_history();
	return (0);
}
