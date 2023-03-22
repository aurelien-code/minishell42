/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:30:11 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/22 20:05:58 by ypages           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tokens	*tokens;
	t_env		*env;
	char		*str_line;

	env = NULL;
	if (!envp || argc > 1)
		return (1);
	(void)argv;
	while (1)
	{
		env = check_env_path(envp);
		if(env->status == NOK)
			return (printf("[ Error ] - Environment not finded\n")NOK);
		str_line = ft_prompt();
		tokens = lexer(str_line);
		parse(str_line, tokens);
	}
	rl_clear_history();
	return (0);
}
