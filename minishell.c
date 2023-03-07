/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:30:11 by aumarin           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/01 15:07:19 by ypages           ###   ########.fr       */
=======
/*   Updated: 2023/03/07 12:06:26 by aumarin          ###   ########.fr       */
>>>>>>> ff43190 (add: lexer)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env *env;
	(void)argv;
<<<<<<< HEAD
	
	env = check_env_path(envp);
	if (argc > 1 || env->status == NOK)
		return (1);
	parse_line(ft_prompt());
=======
	while (1)
	{
		lexer(ft_prompt());
	}
>>>>>>> ff43190 (add: lexer)
	rl_clear_history();
	return (0);
}
