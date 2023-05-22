/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:30:11 by aumarin           #+#    #+#             */
/*   Updated: 2023/05/22 18:49:48 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	t_tokens	*tokens_chars;
	t_line		*tokens_words;
	char		*str_line;
	t_env		*ll_env;
	t_ast		*ast;

	(void)argv;
	if (!envp || argc > 1)
		return (1);
	sig_init();
	ll_env = convert_env(envp);
	str_line = NULL;
	(void)ll_env;
	while (1)
	{
		str_line = ft_prompt();
		if (str_line)
		{
			tokens_chars = lexer(str_line);
			tokens_words = tokens_do(str_line, tokens_chars);
			ast = ft_calloc(get_ast_array_size(&tokens_words), sizeof(t_ast));
			print_ast(parse(ast, &tokens_words));
		}
		else
			sig_ctrl_d();
	}
	rl_clear_history();
	return (0);
}
