/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:30:11 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/02 23:01:57 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

char	**copy_env_in_heap(char **env)
{
	char	**env_cpy;
	int		env_size;
	int		i;

	i = 0;
	env_size = 0;
	while (env[env_size])
		env_size++;
	env_cpy = ft_calloc(env_size + 1, sizeof(char *));
	if (!env_cpy)
		return (NULL);
	while (i < env_size)
	{
		env_cpy[i] = ft_strdup(env[i]);
		i++;
	}
	return (env_cpy);
}

int	main(int argc, char **argv, char **envp)
{
	char		*prompt_line;
	t_lexer		*lexer_line;
	t_tokens	*tokens;
	t_cmd		*commands;
	char		**cpy_env;

	(void)argv;
	if (!envp || argc > 1)
		return (1);
	sig_setup(1);
	prompt_line = NULL;
	cpy_env = copy_env_in_heap(envp);
	prompt_line = ft_prompt();
	while (prompt_line)
	{
		write_history(prompt_line);
		history_size(1);
		lexer_line = lexer(prompt_line);
		if (!lexer_line)
			continue ;
		tokens = get_tokens(prompt_line, lexer_line, cpy_env);
		commands = parser(tokens);
		free_tokens(tokens);
		free(lexer_line);
		if (commands)
		{
			sig_setup(0);
			g_exit_code = executer(commands, &cpy_env);
			sig_setup(1);
			free_commands(commands);
		}
		prompt_line = ft_prompt();
	}
	rl_clear_history();
	ft_putstr_fd("exit\n", 1);
	ft_free_cpy_env(cpy_env);
	return (0);
}
