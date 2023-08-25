/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:30:11 by aumarin           #+#    #+#             */
/*   Updated: 2023/08/25 11:11:41 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*prompt_line;
	t_lexer		*lexer_line;
	t_env		*ll_env;

	(void)argv;
	if (!envp || argc > 1)
		return (1);
	sig_init();
	ll_env = convert_env(envp);
	prompt_line = NULL;
	(void)ll_env;
	while (1)
	{
		prompt_line = ft_prompt();
		if (!prompt_line)
			sig_ctrl_d();
		lexer_line = lexer(prompt_line);
		if (!lexer_line)
			continue ;
		get_tokens(lexer_line);
	}
	(void)lexer_line;
	rl_clear_history();
	return (0);
}
