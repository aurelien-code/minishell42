/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 05:04:06 by n4w4k_            #+#    #+#             */
/*   Updated: 2023/10/02 17:37:40 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	sig_int_handler(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(2, "\n", 1);
	rl_redisplay();
	g_exit_code = 130;
}

void	sig_setup(int mod)
{
	if (mod == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mod == 1)
	{
		signal(SIGINT, sig_int_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
