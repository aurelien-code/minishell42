/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:30:11 by aumarin           #+#    #+#             */
/*   Updated: 2023/08/10 17:19:16 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*str_line;
	t_env		*ll_env;

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
		if (!str_line)
			sig_ctrl_d();
	}
	rl_clear_history();
	return (0);
}
