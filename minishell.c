/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:30:11 by aumarin           #+#    #+#             */
/*   Updated: 2023/02/22 17:00:03 by ypages           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (!envp || argc > 1)
		return (1);
	(void)argv;
	parse_line(ft_prompt());
	ft_exec(argc, argv, envp);
	rl_clear_history();
	return (0);
}
