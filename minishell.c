/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:30:11 by aumarin           #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2023/03/01 15:07:19 by ypages           ###   ########.fr       */
=======
/*   Updated: 2023/03/07 12:06:26 by aumarin          ###   ########.fr       */
>>>>>>> ff43190 (add: lexer)
=======
/*   Updated: 2023/03/20 12:20:01 by aumarin          ###   ########.fr       */
>>>>>>> f4841c6 (save 12/03/22: start main parser part)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
<<<<<<< HEAD
	t_env *env;
=======
	t_tokens	*tokens;
	char		*str_line;

	if (!envp || argc > 1)
		return (1);
>>>>>>> f4841c6 (save 12/03/22: start main parser part)
	(void)argv;
<<<<<<< HEAD
	
	env = check_env_path(envp);
	if (argc > 1 || env->status == NOK)
		return (1);
	parse_line(ft_prompt());
=======
	while (1)
	{
		str_line = ft_prompt();
		tokens = lexer(str_line);
		parse(str_line, tokens);
	}
>>>>>>> ff43190 (add: lexer)
	rl_clear_history();
	return (0);
}
