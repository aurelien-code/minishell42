/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 05:04:06 by n4w4k_            #+#    #+#             */
/*   Updated: 2023/10/02 10:18:21 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_ctrl_d(char **cpy_env)
{
	int	i;

	ft_putstr_fd("exit\n", 1);
	i = 0;
	while (cpy_env[i])
	{
		free(cpy_env[i]);
		i++;
	}
	free(cpy_env);
	exit(0);
}

void	sig_int_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
	else
		printf("unkown signal received %d\n", signum);
}

void	sig_init(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sigemptyset(&sig_int. sa_mask);
	sig_int.sa_sigaction = &sig_int_handler;
	sig_int.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sig_int, NULL);
	sigemptyset(&sig_quit. sa_mask);
	sig_quit.sa_handler = SIG_IGN;
	sig_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sig_quit, NULL);
}
