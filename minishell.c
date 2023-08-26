/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:30:11 by aumarin           #+#    #+#             */
/*   Updated: 2023/08/27 00:23:12 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*prompt_line;
	t_lexer		*lexer_line;
	t_tokens	*tokens;

	(void)argv;
	if (!envp || argc > 1)
		return (1);
	sig_init();
	prompt_line = NULL;
	while (1)
	{
		prompt_line = ft_prompt();
		if (!prompt_line)
			sig_ctrl_d();
		write_history(prompt_line);
		lexer_line = lexer(prompt_line);
		if (!lexer_line)
			continue ;
		tokens = get_tokens(lexer_line);
		free_tokens(tokens);
		free(lexer_line);
	}
	rl_clear_history();
	return (0);
}
